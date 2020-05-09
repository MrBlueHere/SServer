/**
* @author Ladislav Floriš
* @date 05.05.20
*/

#include "CServer.h"
#include "CConfiguration.h"
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
    // Creating socket file descriptor
    m_masterSocket = socket(AF_INET, SOCK_STREAM, 0);

    if (m_masterSocket == 0)
    {
        perror("In socket");
        return false;
    }

    m_address.sin_family = AF_INET;
    m_address.sin_addr.s_addr = config.IpAddressFromString(config.ipAddress);
    cout << m_address.sin_addr.s_addr << endl;
    m_address.sin_port = htons( config.port );

    memset(m_address.sin_zero, '\0', sizeof m_address.sin_zero);

    // Set up log


    // etc.

    return true;
}

int CServer::Listen() {

    int client_socket;
    int addrlen = sizeof(m_address);

    if (bind(m_masterSocket, (struct sockaddr *)&m_address, sizeof(m_address)) < 0)
    {
        perror("In bind");
        exit(EXIT_FAILURE);
    }

    // TODO: Take second argument from config
    if (listen(m_masterSocket, 10) < 0)
    {
        perror("In listen");
        exit(EXIT_FAILURE);
    }

    // Handle requests until server should shut down
    while(!m_awaitingShutdown)
    {
        cout << "\n+++++++ Waiting for new connection ++++++++\n" << endl;

        // Accept request
        client_socket = accept(m_masterSocket, (struct sockaddr *)&m_address, (socklen_t*)&addrlen);
        if (client_socket < 0)
        {
            perror("In accept");
            exit(EXIT_FAILURE);
        }

        // Validate it

        // Handler it and assign thread
        int * p_clientSocket = new int(client_socket);
        thread th(&CServer::HandleConnection, this, p_clientSocket);
        // This thread shouldn't be blocking the main thread, so detach
        th.detach();

        // Return response

    }

    return 0;
}

void CServer::HandleConnection(void * clientSocket) {
    int socket = *(int *)clientSocket;
    delete (int *)clientSocket;

    string hello = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 12\n\nHello world!";
    int valread;
    char buffer[30000] = {0};

    valread = read( socket , buffer, 30000);
    cout << valread << endl;
    printf("%s\n",buffer );
    write(socket , hello.c_str(), hello.size());
    printf("------------------Hello message sent-------------------");
    close(socket);

}

void CServer::Shutdown() {
    // todo

    m_awaitingShutdown = true;
}
