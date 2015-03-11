
# ------------------------- Begin Generic CMake Variable Logging ------------------

# /*	C++ comment style not allowed	*/


# if you are building in-source, this is the same as CMAKE_SOURCE_DIR, otherwise
# this is the top level directory of your build tree
MESSAGE( STATUS "CMAKE_BINARY_DIR:         " ${CMAKE_BINARY_DIR} )

# if you are building in-source, this is the same as CMAKE_CURRENT_SOURCE_DIR, otherwise this
# is the directory where the compiled or generated files from the current CMakeLists.txt will go to
MESSAGE( STATUS "CMAKE_CURRENT_BINARY_DIR: " ${CMAKE_CURRENT_BINARY_DIR} )

# this is the directory, from which cmake was started, i.e. the top level source directory
MESSAGE( STATUS "CMAKE_SOURCE_DIR:         " ${CMAKE_SOURCE_DIR} )

# this is the directory where the currently processed CMakeLists.txt is located in
MESSAGE( STATUS "CMAKE_CURRENT_SOURCE_DIR: " ${CMAKE_CURRENT_SOURCE_DIR} )

# contains the full path to the top level directory of your build tree
MESSAGE( STATUS "PROJECT_BINARY_DIR: " ${PROJECT_BINARY_DIR} )

# contains the full path to the root of your project source directory,
# i.e. to the nearest directory where CMakeLists.txt contains the PROJECT() command
MESSAGE( STATUS "PROJECT_SOURCE_DIR: " ${PROJECT_SOURCE_DIR} )

# set this variable to specify a common place where CMake should put all executable files
# (instead of CMAKE_CURRENT_BINARY_DIR)
MESSAGE( STATUS "EXECUTABLE_OUTPUT_PATH: " ${EXECUTABLE_OUTPUT_PATH} )

# set this variable to specify a common place where CMake should put all libraries
# (instead of CMAKE_CURRENT_BINARY_DIR)
MESSAGE( STATUS "LIBRARY_OUTPUT_PATH:     " ${LIBRARY_OUTPUT_PATH} )

# tell CMake to search first in directories listed in CMAKE_MODULE_PATH
# when you use FIND_PACKAGE() or INCLUDE()
MESSAGE( STATUS "CMAKE_MODULE_PATH: " ${CMAKE_MODULE_PATH} )

# this is the complete path of the cmake which runs currently (e.g. /usr/local/bin/cmake)
MESSAGE( STATUS "CMAKE_COMMAND: " ${CMAKE_COMMAND} )

# this is the CMake installation directory
MESSAGE( STATUS "CMAKE_ROOT: " ${CMAKE_ROOT} )

# this is the filename including the complete path of the file where this variable is used.
MESSAGE( STATUS "CMAKE_CURRENT_LIST_FILE: " ${CMAKE_CURRENT_LIST_FILE} )

# this is linenumber where the variable is used
MESSAGE( STATUS "CMAKE_CURRENT_LIST_LINE: " ${CMAKE_CURRENT_LIST_LINE} )

# this is used when searching for include files e.g. using the FIND_PATH() command.
MESSAGE( STATUS "CMAKE_INCLUDE_PATH: " ${CMAKE_INCLUDE_PATH} )

# this is used when searching for libraries e.g. using the FIND_LIBRARY() command.
MESSAGE( STATUS "CMAKE_LIBRARY_PATH: " ${CMAKE_LIBRARY_PATH} )

# the complete system name, e.g. "Linux-2.4.22", "FreeBSD-5.4-RELEASE" or "Windows 5.1"
MESSAGE( STATUS "CMAKE_SYSTEM: " ${CMAKE_SYSTEM} )

# the short system name, e.g. "Linux", "FreeBSD" or "Windows"
MESSAGE( STATUS "CMAKE_SYSTEM_NAME: " ${CMAKE_SYSTEM_NAME} )

# only the version part of CMAKE_SYSTEM
MESSAGE( STATUS "CMAKE_SYSTEM_VERSION: " ${CMAKE_SYSTEM_VERSION} )

# the processor name (e.g. "Intel(R) Pentium(R) M processor 2.00GHz")
MESSAGE( STATUS "CMAKE_SYSTEM_PROCESSOR: " ${CMAKE_SYSTEM_PROCESSOR} )

# is TRUE on all UNIX-like OS's, including Apple OS X and CygWin
MESSAGE( STATUS "UNIX: " ${UNIX} )

# is TRUE on Windows, including CygWin
MESSAGE( STATUS "WIN32: " ${WIN32} )

# is TRUE on Apple OS X
MESSAGE( STATUS "APPLE: " ${APPLE} )

# is TRUE when using the MinGW compiler in Windows
MESSAGE( STATUS "MINGW: " ${MINGW} )

# is TRUE when using the MSYS developer environment in Windows
MESSAGE( STATUS "MSYS : " ${MSYS} )

# is TRUE on Windows when using the CygWin version of cmake
MESSAGE( STATUS "CYGWIN: " ${CYGWIN} )

# is TRUE on Windows when using a Borland compiler
MESSAGE( STATUS "BORLAND: " ${BORLAND} )

# Microsoft compiler
MESSAGE( STATUS "MSVC: " ${MSVC} )
MESSAGE( STATUS "MSVC_IDE: " ${MSVC_IDE} )
MESSAGE( STATUS "MSVC60: " ${MSVC60} )
MESSAGE( STATUS "MSVC70: " ${MSVC70} )
MESSAGE( STATUS "MSVC71: " ${MSVC71} )
MESSAGE( STATUS "MSVC80: " ${MSVC80} )
MESSAGE( STATUS "CMAKE_COMPILER_2005: " ${CMAKE_COMPILER_2005} )
MESSAGE( STATUS "MSVC90: " ${MSVC90} )
MESSAGE( STATUS "MSVC10: " ${MSVC10} )
MESSAGE( STATUS "MSVC11: " ${MSVC11} )
MESSAGE( STATUS "MSVC12: " ${MSVC12} )
MESSAGE( STATUS "MSVC13: " ${MSVC13} )



# set this to true if you don't want to rebuild the object files if the rules have changed,
# but not the actual source files or headers (e.g. if you changed the some compiler switches)
MESSAGE( STATUS "CMAKE_SKIP_RULE_DEPENDENCY: " ${CMAKE_SKIP_RULE_DEPENDENCY} )

# since CMake 2.1 the install rule depends on all, i.e. everything will be built before installing.
# If you don't like this, set this one to true.
MESSAGE( STATUS "CMAKE_SKIP_INSTALL_ALL_DEPENDENCY: " ${CMAKE_SKIP_INSTALL_ALL_DEPENDENCY} )

# If set, runtime paths are not added when using shared libraries. Default it is set to OFF
MESSAGE( STATUS "CMAKE_SKIP_RPATH: " ${CMAKE_SKIP_RPATH} )

# set this to true if you are using makefiles and want to see the full compile and link
# commands instead of only the shortened ones
MESSAGE( STATUS "CMAKE_VERBOSE_MAKEFILE: " ${CMAKE_VERBOSE_MAKEFILE} )

# this will cause CMake to not put in the rules that re-run CMake. This might be useful if
# you want to use the generated build files on another machine.
MESSAGE( STATUS "CMAKE_SUPPRESS_REGENERATION: " ${CMAKE_SUPPRESS_REGENERATION} )


# A simple way to get switches to the compiler is to use ADD_DEFINITIONS().
# But there are also two variables exactly for this purpose:

# the compiler flags for compiling C sources
MESSAGE( STATUS "CMAKE_C_FLAGS: " ${CMAKE_C_FLAGS} )

# the compiler flags for compiling C++ sources
MESSAGE( STATUS "CMAKE_CXX_FLAGS: " ${CMAKE_CXX_FLAGS} )


# Choose the type of build.  Example: SET(CMAKE_BUILD_TYPE Debug)
MESSAGE( STATUS "CMAKE_BUILD_TYPE: " ${CMAKE_BUILD_TYPE} )

# if this is set to ON, then all libraries are built as shared libraries by default.
MESSAGE( STATUS "BUILD_SHARED_LIBS: " ${BUILD_SHARED_LIBS} )

# the compiler used for C files
MESSAGE( STATUS "CMAKE_C_COMPILER: " ${CMAKE_C_COMPILER} )

# the compiler used for C++ files
MESSAGE( STATUS "CMAKE_CXX_COMPILER: " ${CMAKE_CXX_COMPILER} )

# if the compiler is a variant of gcc, this should be set to 1
MESSAGE( STATUS "CMAKE_COMPILER_IS_GNUCC: " ${CMAKE_COMPILER_IS_GNUCC} )

# if the compiler is a variant of g++, this should be set to 1
MESSAGE( STATUS "CMAKE_COMPILER_IS_GNUCXX : " ${CMAKE_COMPILER_IS_GNUCXX} )

# the tools for creating libraries
MESSAGE( STATUS "CMAKE_AR: " ${CMAKE_AR} )
MESSAGE( STATUS "CMAKE_RANLIB: " ${CMAKE_RANLIB} )

#
#MESSAGE( STATUS ": " ${} )

# ------------------------- End of Generic CMake Variable Logging ------------------


cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(CSGO_MM_Link)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")
include(FindPackageHandleStandardArgs)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

set(CMAKE_AUTOMOC ON)

if(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "-std=c++11")
    set(CMAKE_EXE_LINKER_FLAGS "-l protobuf -pthread")
    set(CMAKE_SHARED_LINKER_FLAGS "-Wl,--no-undefined")
endif()

# steamworks sdk
set(STEAMWORKS_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/../steamworks-sdk/public/steam")


# more steamworks stuff
configure_file("${CMAKE_SOURCE_DIR}/bin/steam_appid.txt" "bin/steam_appid.txt" COPYONLY)

set(STEAMWORKS_REDISTBIN_DIR "${CMAKE_SOURCE_DIR}/../steamworks-sdk/redistributable_bin")
if(WIN32)
    set(STEAMWORKS_LIBRARY "${STEAMWORKS_REDISTBIN_DIR}/steam_api.lib")
    configure_file("${STEAMWORKS_REDISTBIN_DIR}/steam_api.dll" "bin/steam_api.dll" COPYONLY)
else()
    set(STEAMWORKS_LIBRARY "${STEAMWORKS_REDISTBIN_DIR}/linux64/libsteam_api.so")
    configure_file("${STEAMWORKS_LIBRARY}" "bin/libsteam_api.so" COPYONLY)
endif()


find_package(Steamworks REQUIRED)



# protobuf
set(PROTOBUF_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/../protobuf/src")
if(WIN32)
    set(PROTOBUF_LIBRARY "${CMAKE_SOURCE_DIR}/../protobuf/vsprojects/Release/libprotobuf.lib")
    set(PROTOBUF_LIBRARY_DEBUG "${CMAKE_SOURCE_DIR}/../protobuf/vsprojects/Debug/libprotobuf.lib")
endif()
if(WIN32)
    set(PROTOBUF_PROTOC_EXECUTABLE "${CMAKE_CURRENT_SOURCE_DIR}/protoc.exe")
else()
    set(PROTOBUF_PROTOC_EXECUTABLE "${CMAKE_CURRENT_SOURCE_DIR}/protoc")
endif()
find_package(Protobuf REQUIRED)
set(libprotobuf optimized "${PROTOBUF_LIBRARY}" debug "${PROTOBUF_LIBRARY_DEBUG}")
PROTOBUF_GENERATE_CPP(CSTRIKEGCPROTO_SRCS CSTRIKEGCPROTO_HDRS ${CMAKE_CURRENT_SOURCE_DIR}/proto/cstrike15_gcmessages.proto)
PROTOBUF_GENERATE_CPP(STEAMPROTO_SRCS STEAMPROTO_HDRS ${CMAKE_CURRENT_SOURCE_DIR}/proto/steammessages.proto)
PROTOBUF_GENERATE_CPP(GCPROTO_SRCS GCPROTO_HDRS ${CMAKE_CURRENT_SOURCE_DIR}/proto/gcsdk_gcmessages.proto)
PROTOBUF_GENERATE_CPP(GCSYSROTO_SRCS GCSYSPROTO_HDRS ${CMAKE_CURRENT_SOURCE_DIR}/proto/gcsystemmsgs.proto)


if(WIN32)
    set(CSGOMMLINK_EXEEXTRAS "CSGO_MM_Link.rc")
else()
    set(CSGOMMLINK_EXEEXTRAS "")
endif()

#add_executable(CSGO_MM_Link WIN32
add_executable(CSGO_MM_Link
    ${CSGOMMLINK_EXEEXTRAS}
    CSGO_MM_Link/CSGO_MM_Link.h
    CSGO_MM_Link/main.cpp
    CSGO_MM_Link/CSGOClient.h
    CSGO_MM_Link/CSGOClient.cpp
    CSGO_MM_Link/GCMsgHandler.h
    CSGO_MM_Link/CSGOMMLinkObject.h
    CSGO_MM_Link/CSGOMMLinkObject.cpp
    CSGO_MM_Link/CSGOMatchList.h
    CSGO_MM_Link/CSGOMatchList.cpp
    CSGO_MM_Link/CSGOMMHello.h
    CSGO_MM_Link/CSGOMMHello.cpp
    CSGO_MM_Link/CSGOMatchPlayerScore.h
    CSGO_MM_Link/CSGOMatchPlayerScore.cpp
    CSGO_MM_Link/CSGOMatchData.h
    CSGO_MM_Link/CSGOMatchData.cpp
    CSGO_MM_Link/BoilerException.h
    CSGO_MM_Link/BoilerException.cpp
   proto/cstrike15_gcmessages.proto
   proto/steammessages.proto
   proto/gcsdk_gcmessages.proto
   proto/gcsystemmsgs.proto
    ${FILES_H_UIC}
    ${CSTRIKEGCPROTO_SRCS}
    ${CSTRIKEGCPROTO_HDRS}
    ${STEAMPROTO_SRCS}
    ${STEAMPROTO_HDRS}
    ${GCPROTO_SRCS}
    ${GCPROTO_HDRS}
    ${GCSYSPROTO_SRCS}
    ${GCSYSPROTO_HDRS})

#set_target_properties(${PROJECT_NAME} PROPERTIES DEBUG_POSTFIX d)


include_directories("${STEAMWORKS_INCLUDE_DIR}" "${PROTOBUF_INCLUDE_DIR}")

target_link_libraries(CSGO_MM_Link "${STEAMWORKS_LIBRARY}" ${libprotobuf})

# source filter
source_group("Generated Files" FILES
    ${FILES_H_UIC}
    ${CSTRIKEGCPROTO_SRCS}
    ${CSTRIKEGCPROTO_HDRS}
    ${STEAMPROTO_SRCS}
    ${STEAMPROTO_HDRS}
    ${GCPROTO_SRCS}
    ${GCPROTO_HDRS}
    ${GCSYSPROTO_SRCS}
    ${GCSYSPROTO_HDRS})

source_group("Protocol Files" FILES
    proto/cstrike15_gcmessages.proto
    proto/steammessages.proto
    proto/gcsdk_gcmessages.proto
    proto/gcsystemmsgs.proto)





