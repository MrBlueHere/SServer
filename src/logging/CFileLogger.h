/**
* @author Ladislav Floriš
* @date 09.05.20
*/

#pragma once

#include "CLogger.h"
#include <string>
#include <mutex>

/// Logger class responsible for logging to file (thread safe)
class CFileLogger : public CLogger {
public:
    /// Constructor accepting log file as parameter
    explicit CFileLogger(std::string logFile, std::string logFormat, LogLevel level, bool headerOnly);

    /// Default destructor
    ~CFileLogger() = default;

    /// Method for logging information
    /// \param msg to log
    void Info(const std::string & msg) override;

    /// Method for logging warnings
    /// \param msg to log
    void Warn(const std::string & msg) override;

    /// Method for logging errors
    /// \param msg to log
    void Error(const std::string & msg) override;
private:
    /// Where to store logs
    std::string m_logFile;

    /// Mutex for accessing the log file
    std::mutex m_fileMutex;
};


