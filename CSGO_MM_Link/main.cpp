/*
CSGO_MM_Link
    Copyright (C) 2015  Christian 'tabakhase' Hackmann

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.


The software included in this product (contains/is based on/uses) copyrighted software that is licensed under the "GPLv3".
    Boiler          * by Ansas Bogdan

The software included in this product (contains/is based on/uses) copyrighted software that is licensed under the "New BSD License".
    protobuf        * by Google

The software included in this product (contains/is based on/uses) copyrighted software.
    Steamworks SDK  * by Valve Corporation

*/
#include "CSGO_MM_Link.h"

#include <thread>
#include "CSGOMatchList.h"
#include "CSGOMMHello.h"
#include "BoilerException.h"
#include "CSGOMatchData.h"
#include "CSGOMMLinkObject.h"
#ifdef _WIN32
#include <io.h>
#endif
#ifdef _WIN32
#include <windows.h>
#endif
#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <steam/steamtypes.h>



void Error(const char* title, const char* text)
{
    printf("%s: %s\n", title, text);
}


void PrintHelp()
{
    std::cout << "" << CSGO_MM_LINK_BINARYNAME << " - version (" << CSGO_MM_LINK_VERSION << ")" << std::endl
        << " A quick inspection & dumper tool for your past matches data, " << std::endl
        << "  demolinks, roundstats and more" << std::endl
        << " But also a data source tool direclty expose protobuf::Steam-CSGO-GCmessages" << std::endl
        << "  by using a 'real' steam_api.dll in c++ to compensate for Steamworks.NET " << std::endl
        << " " << std::endl
        << "DEFAULT-DEMO (no parameters retranslate to:)" << std::endl
        << "  " << CSGO_MM_LINK_BINARYNAME << " " << "-perf -self -pause"  << std::endl
        << "    -> " << "short past matches performance of YOU + hold in the end" << std::endl
        << " " << std::endl
        << "EXAMPLES " << std::endl
        << "  " << CSGO_MM_LINK_BINARYNAME << " " << "-matches -demo"  << std::endl
        << "    -> " << "your past matches + demolink" << std::endl
        << "  " << CSGO_MM_LINK_BINARYNAME << " " << "-scores"  << std::endl
        << "    -> " << "_all_ playerScores from your past matches" << std::endl
        << "  " << CSGO_MM_LINK_BINARYNAME << " " << "-perf -self -demo"  << std::endl
        << "    -> " << "YOUR past matches performance(+demo) as well as your rank and wins" << std::endl
        << " " << std::endl
        << "SWITCHES-Global " << std::endl
        << "  -h (elp)    " << " print this help text" << std::endl
        << "  -v (erbose) " << " verbose" << std::endl
        << "  -V (ersion) " << " print version information" << std::endl
        << " " << std::endl
        << "SWITCHES-Console (a lot of these supporting -demo)" << std::endl
        << "  -demo                    " << "includes demoLinks in a lot of these outputs, LONG!" << std::endl
        << "  -scores   |  -noscores   " << "past matches detailedScoreboards" << std::endl
        << "  -matches  |  -nomatches  " << "past matches Summary" << std::endl
        << "  -perf     |  -noperf     " << "Your past matches performance in slim readable form" << std::endl
        << "  -self     |  -noself     " << "Your SteamID, AccountID, MM-Rank and recommends" << std::endl
        << "  -laststatus  or  -status " << "console-status like output of your last MM, csgo-whois.com" << std::endl
        << " " << std::endl
        << "SWITCHES-Special " << std::endl
        << "  -pause       " << "adds 'press to exit' to keep the consoleWindow open" << std::endl
        << "  -rawlist     " << "CMsgGCCStrike15_v2_MatchList.SerializeAsString()" << std::endl
        << "  -rawhello    " << "CMsgGCCStrike15_v2_MatchmakingGC2ClientHello.SerializeAsString()" << std::endl
        << "               " << " or better, that was this project was actually made for :P" << std::endl
        << " " << std::endl
    << std::endl;
}

struct stop_now_t { };

int main(int argc, char** argv)
{
    CSGOMMLinkObject linkObj;
    int res = 0;

    bool paramVerbose = false;

    bool paramKeepOpen = false;

    bool paramRawMatchList = false;
    bool paramRawHello = false;

    bool paramWithDemoLink = false;

    bool paramPrintScores = false;
    bool paramPrintMatches = false;
    bool paramPrintPerf = false;
    bool paramPrintSelf = false;
    bool paramPrintLaststatus = false;

    if(argc<=1)
    {
        paramKeepOpen = true;
        PrintHelp();
        std::cout << std::endl;
        std::cout << "---DEMO-ACTIVE---" << " generating '-perf -self -pause', " << std::endl;
        std::cout << " please wait..."  << std::endl;
        std::cout << std::endl;

        //paramPrintScores = true;
        //paramPrintMatches = true;
        paramPrintPerf = true;
        paramPrintSelf = true;
    }

    for( int il=1; il < argc; il = il + 1 )
    {
        std::string option = argv[il];
        if(option == "-h" || option == "--h" || option == "-help" || option == "--help" || option == "/?"){
            PrintHelp();
            return 0;
        }else if(option == "-V" || option == "--V" || option == "-version" || option == "--version"){
            std::cout << "" << CSGO_MM_LINK_BINARYNAME << " - version (" << CSGO_MM_LINK_VERSION << ")" << std::endl;
            return 0;
        }else if(option == "-v" || option == "--v" || option == "-verbose" || option == "--verbose"){
            paramVerbose = true;
        }else if(option == "-p" || option == "--p" || option == "-pause" || option == "--pause"){
            paramKeepOpen = true;
        }else if(option == "-nopause"){ // no param == this param?
            paramKeepOpen = false;
        }else if(option == "-rawlist"){
            paramRawMatchList = true;
        }else if(option == "-rawhello"){
            paramRawHello = true;
        }else if(option == "-status" || option == "-last" || option == "-laststatus" || option == "-statuslast"){
            paramPrintLaststatus = true;
        }else if(option == "-scores"){
            paramPrintScores = true;
        }else if(option == "-noscores"){
            paramPrintScores = false;
        }else if(option == "-matches"){
            paramPrintMatches = true;
        }else if(option == "-nomatches"){
            paramPrintMatches = false;
        }else if(option == "-perf" || option == "-performance"){
            paramPrintPerf = true;
        }else if(option == "-noperf"){
            paramPrintPerf = false;
        }else if(option == "-self"){
            paramPrintSelf = true;
        }else if(option == "-noself"){
            paramPrintSelf = false;
        }else if(option == "-demo" || option == "--demo" || option == "-demolink" || option == "-dem" || option == "--dem"){
            paramWithDemoLink = true;
        }else if(option != ""){
            std::cerr << "ERROR - InvalidArgument: " << option << std::endl;
            std::cerr << "  check '" << CSGO_MM_LINK_BINARYNAME << " -help'" << std::endl << std::endl;
            PrintHelp();
            return 1;
        }
    }

    // usage error? demo is an option paramater, lets fix that for you...
    if(paramWithDemoLink && !(paramPrintMatches || paramPrintPerf)){
        paramPrintMatches = true;
    }


#ifdef _WIN32
    HWND test = FindWindowW(0, L"Counter-Strike: Global Offensive");
    if(test != NULL)
    {
        Error("Warning", "CS:GO is currently running, please close the game first.\n");
        return 1;
    }
#endif

    if(paramVerbose) std::clog << "LINK-VERBOSE:" << "--- START-STEAMINIT ---" << std::endl;

    if (SteamAPI_RestartAppIfNecessary(k_uAppIdInvalid))
        return 1;


#ifdef _WIN32
    int savedStderr;
    if(!paramVerbose) {
        savedStderr =  _dup(_fileno(stderr));
        freopen("NUL", "w", stderr);
    }
#endif

    if (!SteamAPI_Init())
    {
        Error("Fatal Error", "Steam must be running (SteamAPI_Init() failed).\n");
        return 1;
    }

#ifdef _WIN32
    if(!paramVerbose) {
        fflush(stderr);
        _dup2(savedStderr, _fileno(stderr));
        _close(savedStderr);
        clearerr(stderr);
    }
#endif


    if (!SteamUser()->BLoggedOn())
    {
        Error("Fatal Error", "Steam user must be logged in (SteamUser()->BLoggedOn() returned false).\n");
        return 1;
    }


    if(paramVerbose) std::clog << "LINK-VERBOSE:" << "--- END-STEAMINIT ---" << std::endl;

    if(paramVerbose) std::clog << "LINK-VERBOSE:" << "--- START-StartCallbackThread ---" << std::endl;
    bool running = true;
    auto cbthread = std::thread([&running]()
    {
        while (running)
        {
            try
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(CSGO_MM_LINK_STEAM_CALLBACK_INTERVAL));
                Steam_RunCallbacks(GetHSteamPipe(), false);
            }
            catch (BoilerException& e)
            {
                Error("Fatal Error", e.what());
                exit(1);
            }
        };
    });
    if(paramVerbose) std::clog << "LINK-VERBOSE:" << "--- END-StartCallbackThread ---" << std::endl;



    if(paramVerbose) std::clog << "LINK-VERBOSE:" << "--- START-TRY-GcConnect ---" << std::endl;
    bool resGc = false;
    try
    {
        // make sure we are connected to the gc
        if(paramVerbose) std::clog << "LINK-VERBOSE:" << "--- waitFor GcConnect ---" << std::endl;
        CSGOClient::GetInstance()->WaitForGcConnect();
        if(paramVerbose) std::clog << "LINK-VERBOSE:" << "--- got GcConnect ---" << std::endl;
        resGc = true;

        linkObj.account_id = SteamUser()->GetSteamID().GetAccountID();
        linkObj.steam_id = SteamUser()->GetSteamID().ConvertToUint64();
        linkObj.playername = SteamFriends()->GetPersonaName();
    }
    catch (BoilerException& e)
    {
        Error("Fatal error", e.what());
        resGc = false;
    }
    if(paramVerbose) std::clog << "LINK-VERBOSE:" << "--- END-TRY-GcConnect ---" << std::endl;

    if(!resGc)
    {
        Error("Fatal error", "Could not complete GcConnect\n");
        return 1;
    }


    if(paramVerbose) std::clog << "LINK-VERBOSE:" << "--- START-Thread-Hello ---" << std::endl;
    bool resHello = false;
    auto hellothread = std::thread([&linkObj, paramVerbose, &resHello, paramRawHello]()
    {
        try
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(CSGO_MM_LINK_STEAM_HELLO_DELAY)); // this is minimal, and should solve some issues...
            // refresh hello data
            CSGOMMHello mmhello;
            if(paramVerbose) std::clog << "LINK-VERBOSE:" << "--- update MMHello ---" << std::endl;
            mmhello.RefreshWait();
            if(paramVerbose) std::clog << "LINK-VERBOSE:" << "--- got MMHello ---" << std::endl;

            resHello = true;

            if(paramRawHello){
                std::cout << mmhello.exposedProt.SerializeAsString();
                throw stop_now_t();
            }

            std::vector<std::string> ranks = {
                "-unranked-",
                "Siver 1",
                "Siver 2",
                "Siver 3",
                "Siver 4",
                "Siver Elite",
                "Siver Elite Master",
                "Gold Nova 1",
                "Gold Nova 2",
                "Gold Nova 3",
                "Gold Nova 4",
                "Master Guardian 1",
                "Master Guardian 2",
                "Master Guardian Elite",
                "Distinguished Master Guardian",
                "Legendary Eagle",
                "Legendary Eagle Master",
                "SMFC",
                "Global Elite",
            };

            if(mmhello.exposedProt.ranking().has_rank_id())
            {
                linkObj.rank_id = mmhello.exposedProt.ranking().rank_id();
                linkObj.rank_str = ranks[mmhello.exposedProt.ranking().rank_id()];
            }
            if(mmhello.exposedProt.ranking().has_wins())
                linkObj.rank_wins = mmhello.exposedProt.ranking().wins();
            if(mmhello.exposedProt.ranking().has_rank_change())
                linkObj.rank_change = mmhello.exposedProt.ranking().rank_change();

            if(mmhello.exposedProt.commendation().has_cmd_friendly())
                linkObj.cmd_friendly = mmhello.exposedProt.commendation().cmd_friendly();
            if(mmhello.exposedProt.commendation().has_cmd_teaching())
                linkObj.cmd_teaching = mmhello.exposedProt.commendation().cmd_teaching();
            if(mmhello.exposedProt.commendation().has_cmd_leader())
                linkObj.cmd_leader = mmhello.exposedProt.commendation().cmd_leader();

        }
        catch (stop_now_t) {
            return 0;
        }
        catch (CSGO_MM_LinkExceptionTimeout)
        {
            Error("Warning", "Timeout on receiving CMsgGCCStrike15_v2_MatchmakingGC2ClientHello\n");
            resHello = false;
        }
        catch (BoilerException& e)
        {
            Error("Fatal error", e.what());
            resHello = false;
        }
        if(paramVerbose) std::clog << "LINK-VERBOSE:" << "--- END-Thread-Hello ---" << std::endl;
        return 0;
    });




    if(paramVerbose) std::clog << "LINK-VERBOSE:" << "--- START-Thread-MatchList ---" << std::endl;
    bool resList = false;
    auto matchthread = std::thread([&linkObj, paramVerbose, &resList, paramRawMatchList]()
    {
        try
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(CSGO_MM_LINK_STEAM_MATCHLIST_DELAY)); // this is minimal, and should solve some issues...
            // refresh match list
            CSGOMatchList matchlist;
            if(paramVerbose) std::clog << "LINK-VERBOSE:" << "--- update MatchList ---" << std::endl;
            matchlist.RefreshWait();
            if(paramVerbose) std::clog << "LINK-VERBOSE:" << "--- got MatchList ---" << std::endl;

            resList = true;

            if(paramRawMatchList){
                std::cout << matchlist.exposedProt.SerializeAsString();
                throw stop_now_t();
            }

            if(paramVerbose) std::clog << "LINK-VERBOSE:" << "--- START-MATCHLIST ---" << std::endl;


    //      for (CDataGCCStrike15_v2_MatchInfo &match : matchlist.Matches())
            for (auto &match : matchlist.Matches())
            {
                //if(paramVerbose) std::clog << "LINK-VERBOSE:" << "--- START-MATCH ---" << std::endl;

                CDataGCCStrike15_v2_MatchInfo matchinfo = match;
                CMsgGCCStrike15_v2_MatchmakingServerRoundStats roundstats = matchinfo.roundstats();


                CSGOMatchData parsedMatch;

                parsedMatch.matchid = matchinfo.matchid();

                parsedMatch.demolink = roundstats.map();

                parsedMatch.matchtime = matchinfo.matchtime();

                parsedMatch.spectators = roundstats.spectators_count();

                char buffer_local [80];
                time_t rawtime_local = matchinfo.matchtime();
                struct tm * timeinfo_local;
                timeinfo_local = localtime (&rawtime_local);
                strftime (buffer_local,80,"%Y-%m-%d %H:%M:%S",timeinfo_local);
                parsedMatch.matchtime_str = buffer_local;

                char buffer_global [80];
                time_t rawtime_global = matchinfo.matchtime();
                struct tm * timeinfo_global;
                timeinfo_global = gmtime (&rawtime_global);
                strftime (buffer_global,80,"%Y-%m-%d %H:%M:%S",timeinfo_global);


                parsedMatch.result = matchlist.getMatchResultNum(matchinfo);
                parsedMatch.result_str = matchlist.getMatchResult(matchinfo);
                parsedMatch.score_ally = roundstats.team_scores(matchlist.getOwnIndex(matchinfo) >= 5 ? 1 : 0);
                parsedMatch.score_enemy = roundstats.team_scores(matchlist.getOwnIndex(matchinfo) >= 5 ? 0 : 1);



                for (auto &account_id : match.roundstats().reservation().account_ids())
                {
                    //if(paramVerbose) std::clog << "LINK-VERBOSE:" << "--- START-MATCH-PLAYER ---" << std::endl;

                    CSGOMatchPlayerScore player;
                    player.index = matchlist.getPlayerIndex(account_id, matchinfo);
                    player.account_id = account_id;
                    player.steam_id = CSteamID(player.account_id, k_EUniversePublic, k_EAccountTypeIndividual).ConvertToUint64();
                    player.kills = roundstats.kills(player.index);
                    player.assists = roundstats.assists(player.index);
                    player.deaths = roundstats.deaths(player.index);
                    player.mvps = roundstats.mvps(player.index);
                    player.score = roundstats.scores(player.index);

                    parsedMatch.scoreboard.push_back(player);

                    //if(paramVerbose) std::clog << "LINK-VERBOSE:" << "--- END-MATCH-PLAYER ---" << std::endl;
                }

                linkObj.matches.push_back(parsedMatch);

                //if(paramVerbose) std::clog << "LINK-VERBOSE:" << "--- END-MATCH ---" << std::endl;
            }
            if(paramVerbose) std::clog << "LINK-VERBOSE:" << "--- END-MATCHLIST ---" << std::endl;

        }
        catch (stop_now_t) {
            return 0;
        }
        catch (CSGO_MM_LinkExceptionTimeout)
        {
            Error("Warning", "Timeout on receiving CMsgGCCStrike15_v2_MatchList\n");
            resList = false;
        }
        catch (BoilerException& e)
        {
            Error("Fatal error", e.what());
            resList = false;
        }
        if(paramVerbose) std::clog << "LINK-VERBOSE:" << "--- END-Thread-MatchList ---" << std::endl;
        return 0;
    });

    if(paramVerbose) std::clog << "LINK-VERBOSE:" << "--- Waiting for ThreadResults... ---" << std::endl;
    matchthread.join();
    hellothread.join();
    if(paramVerbose) std::clog << "LINK-VERBOSE:" << "--- Waiting for ThreadResults - COMPLETED ---" << std::endl;


    if(paramPrintScores && resList)
    {
        for (auto &match : linkObj.matches)
        {
            std::cout << std::endl;
            for (auto &player : match.scoreboard)
            {
                std::cout << "LINK-OUTPUT:"
                    << "Match(" << match.matchid << "):Player(" << player.steam_id << "):"
                    << player.kills << ":"
                    << player.assists << ":"
                    << player.deaths << ":"
                    << player.mvps << ":"
                    << player.score
                << std::endl;
            }
        }
    }

    if(paramPrintMatches && resList)
    {
        std::cout << std::endl;
        std::cout << "=| "
            << std::setw(19) << std::left << "Match Played" << " | "
            << std::setw(19) << std::left << "MatchID" << " | "
            << std::setw(4) << std::left << "Res." << " | "
            << std::setw(7) << std::left << "Score";
        if(paramWithDemoLink)
            std::cout  << " | "<< std::setw(74) << std::left << "DemoLink" << " |=";
        else
            std::cout  << " |"<< std::setw(3) << std::left << "dem" << "|=";
        std::cout << std::endl;
        for (auto &match : linkObj.matches)
        {
            std::cout << "|| "
                << std::setw(19) << std::left << match.matchtime_str << " | "
                << std::setw(19) << std::right << match.matchid << " | "
                << std::setw(4) << std::left << match.result_str << " | "
                << std::setw(2) << std::right << match.score_ally
                << " : "
                << std::setw(2) << std::right << match.score_enemy;
            if(paramWithDemoLink)
                std::cout  << " | "<< std::setw(74) << std::left << match.demolink << " ||";
            else
                std::cout  << " | "<< std::setw(2) << std::left << "*" << "|=";
            std::cout << std::endl;
        }
    }
    else if(paramPrintMatches)
    {
        Error("\nError", "Steam did not respond in time, could not print -matches\n");
        res = 1;
    }


    if(paramPrintPerf && resList)
    {
        std::cout << std::endl;
        std::cout << "=| "
            << std::setw(19) << std::left << "Match Played" << " | "
            << std::setw(4) << std::left << "Res." << " | "
            << std::setw(7) << std::left << "Score" << " || "
            << std::setw(2) << std::left << "K" << " | "
            << std::setw(2) << std::left << "A" << " | "
            << std::setw(2) << std::left << "D" << " | "
            << std::setw(3) << std::left << "MVP" << "| "
            << std::setw(5) << std::left << "Score";
        if(paramWithDemoLink)
            std::cout  << " || "<< std::setw(74) << std::left << "DemoLink" << " |=";
        else
            std::cout  << " ||"<< std::setw(3) << std::left << "dem" << "|=";
        std::cout << std::endl;

        for (auto &match : linkObj.matches)
        {
            for (auto &player : match.scoreboard)
            {
                if(player.account_id == linkObj.account_id)
                {
                    std::cout << "|| "
                        << std::setw(19) << std::left << match.matchtime_str << " | "
                        << std::setw(4) << std::left << match.result_str << " | "
                        << std::setw(2) << std::right << match.score_ally
                        << " : "
                        << std::setw(2) << std::right << match.score_enemy
                        << " ||"
                        << std::setw(3) << std::right << player.kills << " |"
                        << std::setw(3) << std::right << player.assists << " |"
                        << std::setw(3) << std::right << player.deaths << " |"
                        << std::setw(3) << std::right << player.mvps << " | "
                        << std::setw(5) << std::right << player.score;
                    if(paramWithDemoLink)
                        std::cout << " || " << std::setw(74) << std::left << match.demolink  << " ||";
                    else
                        std::cout << " || " << std::setw(2) << std::left << "*"  << "||";
                    std::cout << std::endl;
                }
            }
        }
    }
    else if(paramPrintPerf)
    {
        Error("\nError", "Steam did not respond in time, could not print -perf\n");
        res = 1;
    }


    if(paramPrintSelf && resHello)
    {
        std::cout << std::endl;

        std::cout << "=| "
            << std::setw(19) << std::right << linkObj.steam_id << " -> "
            << std::setw(47) << std::left << linkObj.playername << " |="
        << std::endl;

        std::cout << "|| "
            << std::setw(14) << std::right << linkObj.rank_wins << " Wins -> "
            << std::setw(32) << std::left << linkObj.rank_str
            << " LVL: " << std::setw(3) << std::right << linkObj.rank_id << "       ||"
        << std::endl;

        std::cout << "|| "
            << std::setw(15) << std::right << "Friendly: " << std::setw(3) << std::right << linkObj.cmd_friendly
            << std::setw(20) << std::right << "Teaching: " << std::setw(3) << std::right << linkObj.cmd_teaching
            << std::setw(20) << std::right << "Leader: " << std::setw(3) << std::right << linkObj.cmd_leader
            << "       ||"
        << std::endl;
    }
    else if(paramPrintSelf)
    {
        Error("\nError", "Steam did not respond in time, could not print -self\n");
        res = 1;
    }


    if(paramPrintLaststatus && resList)
    {
        std::cout << std::endl;
        std::cout << std::endl;
        std::cout << "Printing console-like \"status\" below, copy paste it over to csgo-whois.com" << std::endl;
        std::cout << std::endl;
        std::cout << std::endl;

        if(!linkObj.matches.empty())
        {
            CSGOMatchData match = linkObj.matches.back();
            std::cout << "hostname: MM - (" << match.matchtime_str << ") - "
                      << std::setw(4) << std::left << match.result_str << " ["
                      << std::setw(2) << std::right << match.score_ally
                      << ":"
                      << std::setw(2) << std::right << match.score_enemy
                      << "] "
            << std::endl;
            std::cout << "version : *.*.*.*/* * secure" << std::endl;
            std::cout << "udp/ip  : *.*.*.*:*" << std::endl;
            std::cout << "os      :  None" << std::endl;
            std::cout << "type    :  official dedicated" << std::endl;
            std::cout << "map     : Unknown" << std::endl;
            std::cout << "players : " << match.scoreboard.size() << " humans, 0 bots (" << match.scoreboard.size() << "/0 max) (not hibernating)" << std::endl;
            std::cout << std::endl;
            std::cout << "# userid name uniqueid connected ping loss state rate" << std::endl;

            // for (CSGOMatchPlayerScore &player : match.scoreboard)
            for (auto &player : match.scoreboard)
            {
                std::cout << "# 1 " << player.index << " \""  << "/id/" << player.steam_id << "\" "
                    << "STEAM_0:" << player.account_id % 2 << ":" << player.account_id / 2
                    << " 00:00 1337 0 active 1337"
                << std::endl;
            }
            std::cout << "#end" << std::endl;
            std::cout << std::endl;
            std::cout << std::endl;

        }
    }
    else if(paramPrintLaststatus)
    {
        Error("\nError", "Steam did not respond in time, could not print -status\n");
        res = 1;
    }

    if(paramKeepOpen)
    {
        std::cout << std::endl;
        std::cout << "DONE  press [ENTER] to close...";
        std::cin.get();
    }


    // shutdown
    running = false;
    cbthread.join();
    CSGOClient::Destroy();

    SteamAPI_Shutdown();
    return res;
}
