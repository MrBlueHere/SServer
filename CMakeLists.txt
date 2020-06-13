cmake_minimum_required(VERSION 3.15)
project(SServer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS -pthread)
set(CMAKE_CXX_FLAGS -lstdc++fs )
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -fsanitize=address -Wall -pedantic -Werror")

add_executable(SServer src/main.cpp src/CServer.cpp src/CServer.h src/logging/CLogger.cpp src/logging/CLogger.h src/CFile.cpp src/CFile.h src/CConfiguration.cpp src/CConfiguration.h src/CExecutableScript.cpp src/CExecutableScript.h src/logging/CConsoleLogger.cpp src/logging/CConsoleLogger.h src/logging/CFileLogger.cpp src/logging/CFileLogger.h src/CDirectory.cpp src/CDirectory.h src/CRequest.cpp src/CRequest.h src/logging/LogType.cpp src/logging/LogType.h src/CStaticFile.cpp src/CStaticFile.h)