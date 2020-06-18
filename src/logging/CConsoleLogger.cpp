/**
* @author Ladislav Floriš
* @date 09.05.20
*/

#include "CConsoleLogger.h"
#include <iostream>
#include <string>

using namespace std;

CConsoleLogger::CConsoleLogger(std::string logFormat, LogLevel level, bool headerOnly)
: CLogger(move(logFormat), level, headerOnly)
{ }

void CConsoleLogger::Info(const string & text) {
    cout << text << endl;
}

void CConsoleLogger::Warn(const string & text) {
    cout << text << endl;
}

void CConsoleLogger::Error(const string & text) {
    cout << text << endl;
}
