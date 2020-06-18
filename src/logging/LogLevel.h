/**
* @author Ladislav Floriš
* @date 18.06.20
*/

#pragma once

#include <string>

enum LogLevel {
    Info,
    Warn,
    Error
};

const char * LogLevelToString(LogLevel type);

LogLevel StringToLogLevel(const std::string & type);
