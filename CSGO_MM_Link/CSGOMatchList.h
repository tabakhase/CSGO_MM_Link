#ifndef CSGOMatchList_h__
#define CSGOMatchList_h__
#include <QObject>
#include <condition_variable>
#include "CSGOClient.h"


/**
 * utility class to store and update the match list
 */
class CSGOMatchList : public QObject
{
    Q_OBJECT
public:

    CSGOMatchList();
    ~CSGOMatchList();

    void Refresh();
    void RefreshWait();

    const std::vector<CDataGCCStrike15_v2_MatchInfo>& Matches() const;

private:
    void OnClientWelcome(const CMsgClientWelcome& msg);
    void OnMatchList(const CMsgGCCStrike15_v2_MatchList& msg);
    void LoadOldMatchList();
    void SaveMatchList();

signals:
    void matchesFetched(int num);

private:
    bool m_updateComplete;
    std::condition_variable m_updateCv;
    mutable std::mutex m_matchMutex;
    std::vector<CDataGCCStrike15_v2_MatchInfo> m_matches;
    GCMsgHandler<CMsgGCCStrike15_v2_MatchList> m_matchListHandler;
};

#endif // CSGOMatchList_h__
