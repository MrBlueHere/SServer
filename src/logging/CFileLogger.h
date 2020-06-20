/**
* @author Ladislav Floriš
* @date 09.05.20
*/

#pragma once

#include "CLogger.h"
#include <string>

class CFileLogger : public CLogger {
public:
    /// Constructor accepting log file as parameter
    explicit CFileLogger(std::string logFile, std::string logFormat, LogLevel level, bool headerOnly);

    /// Default copy constructor
    CFileLogger(const CFileLogger &) = default;

    /// Default copy assignment
    CFileLogger & operator = (const CFileLogger &) = default;

    /// Method for logging information
    void Info(const std::string &) override;

    /// Method for logging warnings
    void Warn(const std::string &) override;

    /// Method for logging errors
    void Error(const std::string &) override;
private:
    /// Where to store logs
    std::string m_logFile;
};


