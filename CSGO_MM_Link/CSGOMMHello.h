#ifndef CSGOMMHello_h__
#define CSGOMMHello_h__
#include <condition_variable>
#include "CSGOClient.h"


/**
 * utility class to store and update the match list
 */
class CSGOMMHello
{
public:

    CSGOMMHello();
    ~CSGOMMHello();

    void Refresh();
    void RefreshWait();

    CMsgGCCStrike15_v2_MatchmakingGC2ClientHello exposedProt;

private:
    void OnMMHello(const CMsgGCCStrike15_v2_MatchmakingGC2ClientHello& msg);

private:
    bool m_updateComplete;
    std::condition_variable m_updateCv;
    mutable std::mutex m_mmhelloMutex;
    GCMsgHandler<CMsgGCCStrike15_v2_MatchmakingGC2ClientHello> m_mmhelloHandler;
};

#endif // CSGOMMHello_h__
