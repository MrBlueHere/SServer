/**
* @author Ladislav Floriš
* @date 05.05.20
*/

#include "CServer.h"
#include "CConfiguration.h"
#include "logging/CConsoleLogger.h"
#include "logging/CFileLogger.h"
#include <string>
#include <iostream>
#include <cstring>
#include <thread>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>


using namespace std;


bool CServer::Startup(const CConfiguration & config) {
    // Set up log
    if (config.logType == Console) {
        m_logger = make_unique<CConsoleLogger>(CConsoleLogger());
    }
    else if (config.logType == File) {
        m_logger = make_unique<CFileLogger>(CFileLogger(config.logFile));
    }

    // Creating socket file descriptor
    m_masterSocket = socket(AF_INET, SOCK_STREAM, 0);

    if (m_masterSocket == 0)
    {
        m_logger->Log("Failed to create a master socket");
        return false;
    }

    m_address.sin_family = AF_INET;
    m_address.sin_addr.s_addr = config.IpAddressFromString(config.ipAddress);
    m_address.sin_port = htons( config.port );
    memset(m_address.sin_zero, '\0', sizeof m_address.sin_zero);

    return true;
}

int CServer::Listen() {
    if (bind(m_masterSocket, (struct sockaddr *)&m_address, sizeof(m_address)) < 0)
    {
        m_logger->Log("Failed to bind an address");
        exit(EXIT_FAILURE);
    }

    if (listen(m_masterSocket, m_maxConnections) < 0)
    {
        m_logger->Log("Failed to start listening");
        exit(EXIT_FAILURE);
    }

    int client_socket;
    int addrLen = sizeof(m_address);

    // Handle requests until server should shut down
    while(!m_awaitingShutdown)
    {
        cout << "\n+++++++ Waiting for new connection ++++++++\n" << endl;

        // Accept request
        client_socket = accept(m_masterSocket, (struct sockaddr *)&m_address, (socklen_t*)&addrLen);
        if (client_socket < 0)
        {
            m_logger->Log("Failed to accept the request");
            exit(EXIT_FAILURE);
        }

        // Validate it

        // Handler it and assign thread
        int * p_clientSocket = new int(client_socket);
        thread th(&CServer::HandleConnection, this, p_clientSocket);
        // This thread shouldn't be blocking the main thread, so detach
        th.detach();
    }

    return 0;
}

void CServer::HandleConnection(void * clientSocket) {
    int socket = *(int *)clientSocket;
    delete (int *)clientSocket;

    string hello = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 12\n\nHello world!";
    char buffer[1024] = {0};

    read( socket , buffer, 30000);
    cout << buffer << endl;

    write(socket , hello.c_str(), hello.size());
    printf("------------------Hello message sent-------------------");
    close(socket);
}

void CServer::Shutdown() {
    // todo

    m_awaitingShutdown = true;
}
