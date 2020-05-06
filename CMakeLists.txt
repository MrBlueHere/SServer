cmake_minimum_required(VERSION 3.15)
project(SServer)

set(CMAKE_CXX_STANDARD 14)

add_executable(SServer src/main.cpp src/CServer.cpp src/CServer.h src/Logger.cpp src/Logger.h src/File.cpp src/File.h src/Configuration.cpp src/Configuration.h src/CExecutableScript.cpp src/CExecutableScript.h src/CHeader.cpp src/CHeader.h src/HTMLFile.cpp src/HTMLFile.h src/Image.cpp src/Image.h)