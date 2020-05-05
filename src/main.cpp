#include <iostream>
#include "CServer.h"

int main(int argc, char **argv) {
    CServer server{};

    if (server.Startup())
        return server.Listen();

    // Server failed to start
    // log reason, exception, ...
    return 1;
}