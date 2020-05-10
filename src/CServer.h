/**
* @author Ladislav Floriš
* @date 05.05.20
*/

#pragma once

#include <sys/socket.h>
#include "CConfiguration.h"
#include "logging/CLogger.h"
#include <netinet/in.h>
#include <memory>

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
    bool Startup(const CConfiguration &);

    /// To be called when server should start accepting requests
    int Listen();

    void HandleConnection(void *);

    std::string MapUriToPath(const std::string & uri);

    /// Handle server shutdown
    void Shutdown();

private:
    /// Signal that server should shut down
    bool m_awaitingShutdown{};

    std::unique_ptr<CLogger> m_logger;

    sockaddr_in m_address{};
    int m_masterSocket{0};
    int m_maxConnections{10};
    static const int m_bufferSize{4096};
};
