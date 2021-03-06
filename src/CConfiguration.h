/**
* @author Ladislav Floriš
* @date 05.05.20
*/

#pragma once

#include <string>
#include "logging/LogType.h"
#include "logging/LogLevel.h"
#include <set>

/// Class responsible for handling reading and storing server configuration
class CConfiguration {
public:
    /// Constructor
    CConfiguration();

    /// Forbidden copy constructor
    CConfiguration(const CConfiguration &) = delete;

    /// Forbidden copy assignment
    CConfiguration & operator = (const CConfiguration &) = delete;

    /// Reads the config file content, validates it and fills the member variables
    void ReadConfigurationFromFile(const std::string &);

    /// Fills the appropriate CConfiguration member and throws exception if the arguemnt or value is invalid
    /// \param arg, the CConfiguration member
    /// \param val, the value to assign
    void SetConfigParam(const std::string & arg, std::string & val);

    std::string m_ipAddress;
    bool m_useIPv6;
    uint m_port;
    std::string m_shutdownUrl;
    uint m_maxConnections;

    /// Where should we log? (console, file, database, etc.)
    LogType m_logType;
    /// What level of logs should we log? (Info, Warn, Error)
    LogLevel m_logLevel;
    /// How should individual logs look
    std::string m_logFormat;
    /// Whether only request and response header should be logged
    bool m_headersOnly;
    /// File where to log
    std::string m_logFile;

    /// Root server directory
    std::string m_serverDirectory;

    /// Set of valid parameters in config file
    static const std::set<std::string> m_validParameters;
};
