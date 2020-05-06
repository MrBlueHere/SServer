/**
* @author Ladislav Floriš
* @date 05.05.20
*/

#include "CServer.h"
#include "Configuration.h"
#include <string>
#include <sys/socket.h>
#include <netinet/tcp.h>

using namespace std;


bool CServer::Startup(const Configuration & config) {
    // todo


    // Set up log


    // etc.

    return true;
}

int CServer::Listen() {
    // todo

    // Handle requests until server should shut down
    while(!m_awaitingShutdown) {
        // Accept request

        // Validate it

        // Handler it (assign thread if multithreading), log, etc.

        // Return response
    }

    return 0;
}

void CServer::Shutdown() {
    // todo

    m_awaitingShutdown = true;
}
