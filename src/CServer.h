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
#include <map>

/// Main class responsible for server processes and configuration
class CServer {
public:
    /// Empty constructor
    CServer();

    /// Forbidden copy constructor
    CServer(const CServer &) = delete;

    /// Forbidden copy assignment
    CServer & operator = (const CServer &) = delete;

    /// Default destructor
    ~CServer() = default;

    /// Method to be called when server is started, responsible for configurating the server,
    /// setting up logging, ...
    bool Startup(const CConfiguration &);

    /// To be called when server should start accepting requests
    int Listen();

    /// Handles an incoming connection
    void HandleConnection(void *);

    /// Determines the content type header from the uri
    static std::string GetContentType(const std::string & path);

    std::string MapUriToPath(const std::string & uri);

    /// Logger instance
    std::shared_ptr<CLogger> logger;
private:
    /// Signal that server should shut down
    bool m_awaitingShutdown;

    /// Root server directory
    std::string m_serverDirectory;

    /// Shutdown uri
    std::string m_shutdownUrl;

    sockaddr_in m_address;
    int m_masterSocket;
    int m_maxConnections;
    static const int m_bufferSize;
    static const std::map<std::string, std::string> m_mimeTypes;
};
