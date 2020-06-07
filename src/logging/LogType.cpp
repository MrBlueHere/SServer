/**
* @author Ladislav Floriš
* @date 07.06.20
*/

#include "LogType.h"
#include <iostream>

using namespace std;

const char * LogTypeToString(LogType type) {
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

LogType StringToLogType(const std::string & type)
{
    if (type == "Console")
        return Console;
    else if (type == "File")
        return File;
    else
        return NotSet;
}
