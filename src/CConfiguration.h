/**
* @author Ladislav Floriš
* @date 05.05.20
*/

#pragma once

#include <string>
#include "logging/LogType.h"

/// Class responsible for handling reading and storing server configuration
class CConfiguration {
public:
    CConfiguration() = default;

    // TODO: Copy constructor
    // TODO: = operator
    // TODO: Destructor

    bool ReadConfigurationFromFile(const std::string &);

    unsigned int IpAddressFromString(const std::string &) const;

    std::string ipAddress{"127.0.0.1"};
    uint port{8080};
    std::string shutdownUrl;
    uint maxConnections{10};

    /// Where should we log? (console, file, database, etc.)
    LogType logType{Console};
    std::string logFile{""};
};
