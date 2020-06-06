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
    explicit CConfiguration() = default;

    // TODO: Copy constructor
    // TODO: = operator
    // TODO: Destructor

    void ReadConfigurationFromFile(const std::string &);

    unsigned int IpAddressFromString(const std::string &) const;

    void SetConfigParam(const std::string & arg, std::string & val);

    std::string m_ipAddress{"127.0.0.1"};
    uint m_port{8080};
    std::string m_shutdownUrl;
    uint m_maxConnections{10};

    /// Where should we log? (console, file, database, etc.)
    LogType m_logType{Console};
    std::string m_logFile{""};

    std::string m_serverDirectory;

    const std::set<std::string> m_validParameters {
        "IPAddress", "Port", "ShutdownUrl", "MaxConnections", "LogType", "LogFile", "ServerDirectory"
    };
};
