/**
* @author Ladislav Floriš
* @date 09.05.20
*/

#include "CFileLogger.h"
#include "CLog.h"
#include <string>
#include <ostream>
#include <fstream>
#include <utility>
#include <filesystem>

using namespace std;

/// Constructs the object and also creates a a file if it doesn't exist
CFileLogger::CFileLogger(string logFile, string logFormat, LogLevel level, bool headerOnly)
: CLogger(move(logFormat), level, headerOnly), m_logFile(move(logFile))
{
    if (!filesystem::exists(m_logFile)) {
        filesystem::path path{ m_logFile };
        auto parPath = path.parent_path();
        if (parPath != "")
            filesystem::create_directories(parPath);
        ofstream ofs(path);
        ofs << "";
        ofs.close();
    }
}

void CFileLogger::Info(const std::string & text) {
    if (ShouldMessageGetLogged(LogLevel::Info)) {
        CLog log(text, LogLevel::Info);

        lock_guard<std::mutex> guard(m_fileMutex);

        ofstream logFile;
        logFile.open(m_logFile, ios_base::app);
        if (!logFile.is_open()) {
            throw runtime_error("Could not open file");
        }
        logFile << log.GetFormatted(m_logFormat) << endl;
        logFile.close();
    }
}

void CFileLogger::Warn(const string & text) {
    if (ShouldMessageGetLogged(LogLevel::Warn)) {
        CLog log(text, LogLevel::Warn);

        lock_guard<std::mutex> guard(m_fileMutex);

        ofstream logFile;
        logFile.open(m_logFile, ios_base::app);
        if (!logFile.is_open()) {
            throw runtime_error("Could not open file");
        }
        logFile << log.GetFormatted(m_logFormat) << endl;
        logFile.close();
    }
}

void CFileLogger::Error(const string & text) {
    if (ShouldMessageGetLogged(LogLevel::Error)) {
        CLog log(text, LogLevel::Error);

        lock_guard<std::mutex> guard(m_fileMutex);

        ofstream logFile;
        logFile.open(m_logFile, ios_base::app);
        if (!logFile.is_open()) {
            throw runtime_error("Could not open file");
        }
        logFile << log.GetFormatted(m_logFormat) << endl;
        logFile.close();
    }
}
