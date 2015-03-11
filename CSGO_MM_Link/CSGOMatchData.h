#ifndef CSGOMatchData_h__
#define CSGOMatchData_h__
#include <vector>
#include <string>
#include <steam/steamtypes.h>
#include "CSGOMatchPlayerScore.h"


struct CSGOMatchData
{

    public:
        uint64 matchid;

        std::string demolink;

        time_t matchtime;
        std::string matchtime_str;

        uint32 spectators;

        std::vector<CSGOMatchPlayerScore> scoreboard;

        int result;
        std::string result_str;

        int score_ally;
        int score_enemy;
};


#endif // CSGOMatchData_h__
