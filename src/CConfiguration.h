/**
* @author Ladislav Floriš
* @date 05.05.20
*/

#pragma once

#include <string>
#include "logging/LogType.h"
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

    void ReadConfigurationFromFile(const std::string &);

    void SetConfigParam(const std::string & arg, std::string & val);

    std::string m_ipAddress;
    bool m_useIPv6;
    uint m_port;
    std::string m_shutdownUrl;
    uint m_maxConnections;

    /// Where should we log? (console, file, database, etc.)
    LogType m_logType;
    std::string m_logFile;

    std::string m_serverDirectory;

    const std::set<std::string> m_validParameters;
};
