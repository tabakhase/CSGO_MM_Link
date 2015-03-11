#ifndef CSGOMMLinkObject_h__
#define CSGOMMLinkObject_h__
#include <vector>
#include <steam/steamtypes.h>
#include "CSGOMatchData.h"


class CSGOMMLinkObject
{
public:
    uint32 account_id;
    uint64 steam_id;
    std::string playername;

    uint32 rank_id=0;
    std::string rank_str;
    uint32 rank_wins=0;
    float  rank_change;

    uint32 cmd_friendly=0;
    uint32 cmd_teaching=0;
    uint32 cmd_leader=0;

    std::vector<CSGOMatchData> matches;
};

#endif // CSGOMMLinkObject_h__
