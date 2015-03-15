CSGO_MM_Link (for Windows & Linux64(32))
=========
	A quick inspection & dumper tool for your past matches data,
			demolinks, roundstats and more
	But also a data source tool direclty expose protobuf::Steam-CSGO-GCmessages
			by using a 'real' steam_api.dll in c++ hooking into your local running SteamClient.

#** Use at OWN risk ** #


Downloads (precompiled)
=========
* alpha [v0.9.2 Windows](https://github.com/tabakhase/CSGO_MM_Link/releases/tag/0.9.2)


Usage
=========
DEFAULT-DEMO (no parameters retranslate to:)
--------
	CSGO_MM_Link.exe -perf -self -pause
			-> short past matches performance of YOU + hold in the end

EXAMPLES
--------
	CSGO_MM_Link.exe -matches -demo
			-> your past matches + demolink
	CSGO_MM_Link.exe -scores
			-> _all_ playerScores from your past matches
	CSGO_MM_Link.exe -perf -self -demo
			-> YOUR past matches performance(+demo) as well as your rank and wins

SWITCHES-Global
--------
	-h (elp)     print this help text
	-v (erbose)  verbose
	-V (ersion)  print version information

SWITCHES-Console (a lot of these supporting -demo)
--------
	-demo                    includes demoLinks in a lot of these outputs, LONG!
	-scores   |  -noscores   past matches detailedScoreboards
	-matches  |  -nomatches  past matches Summary
	-perf     |  -noperf     Your past matches performance in slim readable form
	-self     |  -noself     Your SteamID, AccountID, MM-Rank and recommends
	-laststatus  or  -status console-status like output of your last MM, csgo-whois.com

SWITCHES-Special
--------
	-pause       adds 'press to exit' to keep the consoleWindow open
	-rawlist     CMsgGCCStrike15_v2_MatchList.SerializeAsString()
	-rawhello    CMsgGCCStrike15_v2_MatchmakingGC2ClientHello.SerializeAsString()
					or better, that was this project was actually made for :P




Build instructions
=========
Dependencies
--------
* [Steamworks SDK](https://partner.steamgames.com/home)
* [CSGO Protbufs](https://github.com/SteamDatabase/GameTracking/tree/master/Protobufs/csgo)
* [protobuf](https://developers.google.com/protocol-buffers/docs/downloads)
* [cmake](http://www.cmake.org/download/)

Building
--------
1. generate project files with cmake
2. compile
