/**
* @author Ladislav Floriš
* @date 19.06.20
*/

#include "CLog.h"
#include <ctime>
#include <chrono>
#include <sstream>

using namespace std;

CLog::CLog(std::string msg, LogLevel level) : m_logLevel(level),  m_message(move(msg)) {
    time_t time = chrono::system_clock::to_time_t(chrono::system_clock::now());
    std::string timeString = std::ctime(&time);
    timeString.resize(timeString.size() - 1);
    m_time = timeString;
}

string CLog::GetFormatted(const string & format) {
    string result = format;

    result = FillVariable(result, "logLevel", LogLevelToString(m_logLevel));
    result = FillVariable(result, "time", m_time);
    result = FillVariable(result, "message", m_message);

    return result;
}

string CLog::FillVariable(string & result, const string & key, const string & val) {
    ostringstream oss;
    oss << '@' << key << '@';

    size_t pos = result.find(oss.str());

    if (pos != string::npos) {
        result.replace(pos, oss.str().size(), val);
    }
    return result;
}