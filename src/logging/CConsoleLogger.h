/**
* @author Ladislav Floriš
* @date 09.05.20
*/

#pragma once

#include "CLogger.h"
#include <string>

class CConsoleLogger : public CLogger {
public:
    /// Default constructor
    CConsoleLogger(std::string logFormat, LogLevel level, bool headerOnly);

    /// Default copy constructor
    CConsoleLogger(const CConsoleLogger &) = default;

    /// Default copy assignment
    CConsoleLogger & operator = (const CConsoleLogger &) = default;

    /// Method for logging information
    void Info(const std::string &) override;

    /// Method for logging warnings
    void Warn(const std::string &) override;

    /// Method for logging errors
    void Error(const std::string &) override;
};


