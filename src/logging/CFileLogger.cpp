/**
* @author Ladislav Floriš
* @date 09.05.20
*/

#include "CFileLogger.h"
#include <string>
#include <ostream>
#include <fstream>
#include <utility>

using namespace std;

CFileLogger::CFileLogger(string logFile, string logFormat, LogLevel level, bool headerOnly)
: CLogger(move(logFormat), level, headerOnly), m_logFile(move(logFile))
{ }

void CFileLogger::Info(const std::string & text) {
    ofstream logFile;
    logFile.open (m_logFile);
    if (!logFile.is_open()) {
        throw runtime_error("Could not open file");
    }

    logFile << text << endl;
    logFile.close();
}

void CFileLogger::Warn(const string &) {

}

void CFileLogger::Error(const string &) {

}
