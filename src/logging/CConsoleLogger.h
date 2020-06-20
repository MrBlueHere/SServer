/**
* @author Ladislav Floriš
* @date 09.05.20
*/

#pragma once

#include "CLogger.h"
#include <string>

/// Logger class responsible for logging to console
class CConsoleLogger : public CLogger {
public:
    /// Default constructor
    CConsoleLogger(std::string logFormat, LogLevel level, bool headerOnly);

    /// Default copy constructor
    CConsoleLogger(const CConsoleLogger &) = default;

    /// Default copy assignment
    CConsoleLogger & operator = (const CConsoleLogger &) = default;

    /// Default destructor
    ~CConsoleLogger() = default;

    /// Method for logging information
    /// \param msg to log
    void Info(const std::string & msg) override;

    /// Method for logging warnings
    /// \param msg to log
    void Warn(const std::string & msg) override;

    /// Method for logging errors
    /// \param msg to log
    void Error(const std::string & msg) override;
};


