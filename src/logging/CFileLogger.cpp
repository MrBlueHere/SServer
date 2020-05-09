/**
* @author Ladislav Floriš
* @date 09.05.20
*/

#include "CFileLogger.h"
#include <iostream>
#include <string>
#include <ostream>
#include <fstream>
#include <utility>

using namespace std;

CFileLogger::CFileLogger(string logFile) : m_logFile(move(logFile)) {}

void CFileLogger::Log(const std::string & text) {
    ofstream logFile;
    logFile.open (m_logFile);
    if (!logFile.is_open()) {
        throw runtime_error("Could not open file");
    }

    logFile << text << endl;
    logFile.close();
}
