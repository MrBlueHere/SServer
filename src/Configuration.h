/**
* @author Ladislav Floriš
* @date 05.05.20
*/

#pragma once

#include <string>

/// Class responsible for handling reading and storing server configuration
class Configuration {
public:
    Configuration() = default;

    // TODO: Copy constructor
    // TODO: = operator
    // TODO: Destructor

    bool ReadConfigurationFromFile(const std::string &src);

    std::string ipAddress;
    uint port;
    std::string shutdownUrl;
    /// Where should we log? (console, file, database, etc.)
    std::string logType;
};
