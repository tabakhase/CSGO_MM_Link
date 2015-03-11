#include "CSGOMatchList.h"
#include <QFile>
#include "BoilerException.h"

CSGOMatchList::CSGOMatchList() 
    :m_matchListHandler(this, &CSGOMatchList::OnMatchList)
{
    LoadOldMatchList();
    CSGOClient::GetInstance()->RegisterHandler(k_EMsgGCCStrike15_v2_MatchList, &m_matchListHandler);
}

CSGOMatchList::~CSGOMatchList()
{
    SaveMatchList();
    CSGOClient::GetInstance()->RemoveHandler(k_EMsgGCCStrike15_v2_MatchList, &m_matchListHandler);
}

void CSGOMatchList::LoadOldMatchList()
{
    QFile f(QString("%1_matchlist.dat").arg(SteamUser()->GetSteamID().GetAccountID()));
    if (f.exists())
    {
        f.open(QIODevice::ReadOnly);
        CMsgGCCStrike15_v2_MatchList matchlist;
        if (matchlist.ParseFromFileDescriptor(f.handle()))
        {
            for (auto& m : matchlist.matches())
                m_matches.push_back(m);
        }
        emit matchesFetched(m_matches.size());
    }
}

void CSGOMatchList::SaveMatchList()
{
    QFile f(QString("%1_matchlist.dat").arg(SteamUser()->GetSteamID().GetAccountID()));
    f.open(QIODevice::WriteOnly);

    CMsgGCCStrike15_v2_MatchList matchlist;
    for (auto& m : m_matches)
        matchlist.add_matches()->CopyFrom(m);

    matchlist.SerializePartialToFileDescriptor(f.handle());
}

void CSGOMatchList::OnMatchList(const CMsgGCCStrike15_v2_MatchList& msg)
{
    std::unique_lock<std::mutex> lock(m_matchMutex);
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
    emit matchesFetched(m_matches.size() - oldCount);
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
    while (!m_updateComplete)
        m_updateCv.wait(lock);
}

const std::vector<CDataGCCStrike15_v2_MatchInfo>& CSGOMatchList::Matches() const
{
    std::lock_guard<std::mutex> lock(m_matchMutex);
    return m_matches;
}
