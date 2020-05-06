/**
* @author Ladislav Floriš
* @date 05.05.20
*/

#pragma once

#include <sys/socket.h>
#include "Configuration.h"
#include <netinet/tcp.h>

/// Main class responsible for server processes and configuration
class CServer {
public:
    /// Default constructor
    CServer() = default;

    /// Forbidden copy constructor
    CServer(const CServer &) = delete;

    /// Forbidden copy assignment
    CServer & operator = (const CServer &) = delete;

    /// Default destructor
    // TODO: Is there anything to free?
    ~CServer() = default;

    /// Method to be called when server is started, responsible for configurating the server,
    /// setting up logging, ...
    bool Startup(const Configuration &);

    /// To be called when server should start accepting requests
    int Listen();

    /// Handle server shutdown
    void Shutdown();

private:
    /// Signal that server should shut down
    bool m_awaitingShutdown;
};
