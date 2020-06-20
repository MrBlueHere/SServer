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

/// Converts the given LogType to it's string representation
/// \param type
/// \return
const char * LogTypeToString(LogType type);

/// Converts the given string to LogType enum
/// \param type
/// \return
LogType StringToLogType(const std::string & type);
