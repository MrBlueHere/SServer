/**
* @author Ladislav Floriš
* @date 18.06.20
*/

#include "LogLevel.h"

using namespace std;

const char * LogLevelToString(LogLevel type) {
    switch (type)
    {
        case Info:
            return "Info";
        case Warn:
            return "Warn";
        case Error:
            return "Info";
    }
    return "Info";
}

LogLevel StringToLogLevel(const std::string & type)
{
    if (type == "Info")
        return Info;
    else if (type == "Warn")
        return Warn;
    else if (type == "Error")
        return Error;
    return Info;
}
