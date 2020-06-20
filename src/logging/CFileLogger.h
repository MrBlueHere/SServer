/**
* @author Ladislav Floriš
* @date 09.05.20
*/

#pragma once

#include "CLogger.h"
#include <string>
#include <mutex>

class CFileLogger : public CLogger {
public:
    /// Constructor accepting log file as parameter
    explicit CFileLogger(std::string logFile, std::string logFormat, LogLevel level, bool headerOnly);

    /// Method for logging information
    void Info(const std::string &) override;

    /// Method for logging warnings
    void Warn(const std::string &) override;

    /// Method for logging errors
    void Error(const std::string &) override;
private:
    /// Where to store logs
    std::string m_logFile;

    /// Mutex for accessing the log file
    std::mutex m_fileMutex;
};


