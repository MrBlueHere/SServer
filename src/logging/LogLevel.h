/**
* @author Ladislav Floriš
* @date 18.06.20
*/

#pragma once

#include <string>

/// Enum describing the levels of logs
enum LogLevel {
    Info,
    Warn,
    Error
};

/// Converts the given LogLevel to it's string representation
/// \param type
/// \return
const char * LogLevelToString(LogLevel type);

/// Converts the given string to LogLevel enum
/// \param type
/// \return
LogLevel StringToLogLevel(const std::string & type);
