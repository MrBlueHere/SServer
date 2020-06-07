/**
* @author Ladislav Floriš
* @date 07.06.20
*/

#pragma once

#include <string>

enum LogType {
    NotSet,
    Console,
    File
};

const char * LogTypeToString(LogType type);

LogType StringToLogType(const std::string & type);
