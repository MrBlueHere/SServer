/**
* @author Ladislav Floriš
* @date 19.06.20
*/

#pragma once

#include <string>
#include "LogLevel.h"

/// Class representing the log, capable of formatting a given log message to a uniform form
class CLog {
public:
    /// Constructor accepting the message to be logged and log level
    CLog(std::string msg, LogLevel level);

    /// Default copy constructor
    CLog(const CLog &) = default;

    /// Default copy assignment
    CLog & operator = (const CLog &) = default;

    /// Default destructor
    ~CLog() = default;

    /// Formats the given message using the m_logFormat
    std::string GetFormatted(const std::string & format);
private:
    /// Looks for the key in the result and replaces it with val if found
    std::string FillVariable(std::string & result, const std::string & key, const std::string & val);

    /// Log Level
    LogLevel m_logLevel;

    /// Message to be logged
    std::string m_message;

    /// Time of the log
    std::string m_time;
};


