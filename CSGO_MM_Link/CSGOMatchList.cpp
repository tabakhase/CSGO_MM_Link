#include "CSGO_MM_Link.h"
#include "CSGOMatchList.h"
#include "BoilerException.h"
#include <thread>
#include <iostream>
#include <algorithm>

CSGOMatchList::CSGOMatchList() 
    :m_matchListHandler(this, &CSGOMatchList::OnMatchList)
{
    CSGOClient::GetInstance()->RegisterHandler(k_EMsgGCCStrike15_v2_MatchList, &m_matchListHandler);
}

CSGOMatchList::~CSGOMatchList()
{
    CMsgGCCStrike15_v2_MatchList matchlist;
    for (auto& m : m_matches)
        matchlist.add_matches()->CopyFrom(m);
    CSGOClient::GetInstance()->RemoveHandler(k_EMsgGCCStrike15_v2_MatchList, &m_matchListHandler);
}


void CSGOMatchList::OnMatchList(const CMsgGCCStrike15_v2_MatchList& msg)
{
    std::unique_lock<std::mutex> lock(m_matchMutex);
    exposedProt = msg;
    size_t oldCount = m_matches.size();
    for (auto it = msg.matches().rbegin(); it != msg.matches().rend(); ++it)
    {
        auto oldmatch = std::find_if(m_matches.begin(), m_matches.end(), [it](CDataGCCStrike15_v2_MatchInfo& info)
        {
            return info.matchid() == it->matchid();
        });

        if (oldmatch == m_matches.end())
            m_matches.push_back(*it);
    }
    m_updateComplete = true;
    lock.unlock();
    m_updateCv.notify_all();
}

void CSGOMatchList::Refresh()
{
    CMsgGCCStrike15_v2_MatchListRequestRecentUserGames request;
    request.set_accountid(SteamUser()->GetSteamID().GetAccountID());
    if (CSGOClient::GetInstance()->SendGCMessage(k_EMsgGCCStrike15_v2_MatchListRequestRecentUserGames, &request) != k_EGCResultOK)
        throw BoilerException("Failed to send EMsgGCCStrike15_v2_MatchListRequestRecentUserGames");
}

void CSGOMatchList::RefreshWait()
{
    m_updateComplete = false;
    Refresh();
    std::unique_lock<std::mutex> lock(m_matchMutex);

    m_updateCv.wait_for(lock, std::chrono::milliseconds(CSGO_MM_LINK_STEAM_CMSG_TIMEOUT));
    if(!m_updateComplete)
        throw CSGO_MM_LinkExceptionTimeout();
}

const std::vector<CDataGCCStrike15_v2_MatchInfo>& CSGOMatchList::Matches() const
{
    std::lock_guard<std::mutex> lock(m_matchMutex);
    return m_matches;
}


int CSGOMatchList::getOwnIndex(const CDataGCCStrike15_v2_MatchInfo& info)
{
    uint32 accid = SteamUser()->GetSteamID().GetAccountID();
    for (int i = 0; i < info.roundstats().reservation().account_ids().size(); ++i)
        if (info.roundstats().reservation().account_ids(i) == accid)
            return i;
    throw "unable to find own accid in matchinfo";
}

int CSGOMatchList::getPlayerIndex(uint32 accid, const CDataGCCStrike15_v2_MatchInfo& info)
{
    //uint32 accid = SteamUser()->GetSteamID().GetAccountID();
    for (int i = 0; i < info.roundstats().reservation().account_ids().size(); ++i)
        if (info.roundstats().reservation().account_ids(i) == accid)
            return i;
    throw "unable to find specified accid in matchinfo";
}

std::string CSGOMatchList::getMatchResult(const CDataGCCStrike15_v2_MatchInfo& info)
{
    if (info.roundstats().match_result() == 0)
        return "TIE";
    if (info.roundstats().match_result() == 1 && getOwnIndex(info) <= 4)
        return "WIN";
    if (info.roundstats().match_result() == 2 && getOwnIndex(info) >= 5)
        return "WIN";
    return "LOSS";
}

int CSGOMatchList::getMatchResultNum(const CDataGCCStrike15_v2_MatchInfo& info)
{
    if (info.roundstats().match_result() == 0)
        return 0; // tie
    if (info.roundstats().match_result() == 1 && getOwnIndex(info) <= 4)
        return 1; // win
    if (info.roundstats().match_result() == 2 && getOwnIndex(info) >= 5)
        return 1; // win
    return 2; // loss
}
