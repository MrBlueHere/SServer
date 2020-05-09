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
    explicit CFileLogger(std::string logFile);

    /// Default copy constructor
    CFileLogger(const CFileLogger &) = default;

    /// Default copy assignment
    CFileLogger & operator = (const CFileLogger &) = default;

    void Log(const std::string &) override;

private:
    std::string m_logFile;
};


