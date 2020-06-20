/**
* @author Ladislav Floriš
* @date 05.05.20
*/

#pragma once

#include <string>
#include <vector>
#include "../CRequest.h"
#include "LogLevel.h"

/// Abstract Base class responsible for logging, other logger classes are derived from this class
class CLogger {
public:
    CLogger(std::string logFormat, LogLevel level, bool headerOnly);

    /// Pure virtual method for logging information
    virtual void Info(const std::string &) = 0;

    /// Pure virtual method for logging warnings
    virtual void Warn(const std::string &) = 0;

    /// Pure virtual method for logging errors
    virtual void Error(const std::string &) = 0;

    /// Format in which logs are written
    std::string m_logFormat;

    /// What kind of logs should be writen
    LogLevel m_logLevel;

    /// Should only the request and response header be writen
    bool m_headerOnly;

protected:
    /// Checks whether the logger should log at this level
    bool ShouldMessageGetLogged(LogLevel level) const;
};
