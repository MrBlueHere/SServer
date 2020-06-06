#include <iostream>
#include "CServer.h"
#include "logging/LogType.h"

using namespace std;

int main(int argc, char **argv) {
    CServer server{};

    // IP should be configurable, server could listen on private or public IPs or both (also IPv6)
    CConfiguration config{};
    config.ReadConfigurationFromFile("config.txt");

    if (server.Startup(config))
        return server.Listen();

    // Server failed to start
    perror("Server failed to start");

    return 1;
}