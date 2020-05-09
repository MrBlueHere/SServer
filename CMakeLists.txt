cmake_minimum_required(VERSION 3.15)
project(SServer)

set(CMAKE_CXX_STANDARD 17)

add_executable(SServer src/main.cpp src/CServer.cpp src/CServer.h src/CLogger.cpp src/CLogger.h src/CFIle.cpp src/CFIle.h src/CConfiguration.cpp src/CConfiguration.h src/CExecutableScript.cpp src/CExecutableScript.h src/CHeader.cpp src/CHeader.h src/CHTMLFile.cpp src/CHTMLFile.h src/CImage.cpp src/CImage.h)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -Wall -pedantic -Werror")