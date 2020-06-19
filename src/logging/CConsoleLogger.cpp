/**
* @author Ladislav Floriš
* @date 09.05.20
*/

#include "CConsoleLogger.h"
#include "CLog.h"
#include <iostream>
#include <string>

using namespace std;

CConsoleLogger::CConsoleLogger(std::string logFormat, LogLevel level, bool headerOnly)
: CLogger(move(logFormat), level, headerOnly)
{ }

void CConsoleLogger::Info(const string & text) {
    CLog log(text, LogLevel::Info);
    cout << log.GetFormatted(m_logFormat) << endl;
}

void CConsoleLogger::Warn(const string & text) {
    CLog log(text, LogLevel::Warn);
    cout << log.GetFormatted(m_logFormat) << endl;
}

void CConsoleLogger::Error(const string & text) {
    CLog log(text, LogLevel::Error);
    cout << log.GetFormatted(m_logFormat) << endl;
}
