/**
* @author Ladislav Floriš
* @date 05.05.20
*/

#include "CServer.h"

using namespace std;

bool CServer::Startup() {
    // todo

    // Read configuration

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
