#include <iostream>
#include "CServer.h"
#include "logging/LogType.h"

int main(int argc, char **argv) {
    CServer server{};

    // TODO: Initialize configuration
    // IP should be configurable, server could listen on private or public IPs or both (also IPv6)
    CConfiguration config{};
    config.ipAddress = "127.0.0.1";
    config.port = 8080;
    config.maxConnections = 20;
    config.logType = Console;

    if (server.Startup(config))
        return server.Listen();

    // Server failed to start
    // log reason, exception, ...
    return 1;
}