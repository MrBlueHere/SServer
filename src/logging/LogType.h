/**
* @author Ladislav Floriš
* @date 09.05.20
*/

#pragma once

enum LogType {
    NotSet,
    Console,
    File
};

inline const char* LogTypeToString(LogType type)
{
    switch (type)
    {
        case Console:
            return "Console";
        case File:
            return "File";
        default:
            return "NotSet";
    }
}

inline const LogType StringToLogType(const std::string & type)
{
    if (type == "Console")
        return Console;
    else if (type == "File")
        return File;
    else
        return NotSet;
}