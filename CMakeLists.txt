cmake_minimum_required(VERSION 3.15)
project(SServer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS -pthread)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lstdc++fs -Wall -pedantic -Werror")
link_libraries(stdc++fs)

add_executable(SServer src/main.cpp src/CServer.cpp src/CServer.h src/logging/CLogger.cpp src/logging/CLogger.h src/CFile.cpp src/CFile.h src/CConfiguration.cpp src/CConfiguration.h src/CExecutableScript.cpp src/CExecutableScript.h src/logging/CConsoleLogger.cpp src/logging/CConsoleLogger.h src/logging/CFileLogger.cpp src/logging/CFileLogger.h src/CDirectory.cpp src/CDirectory.h src/CRequest.cpp src/CRequest.h src/logging/LogType.cpp src/logging/LogType.h src/CStaticFile.cpp src/CStaticFile.h src/CError.cpp src/CError.h src/logging/LogLevel.cpp src/logging/LogLevel.h src/logging/CLog.cpp src/logging/CLog.h src/CShutdown.cpp src/CShutdown.h)