/**
* @author Ladislav Floriš
* @date 05.05.20
*/

#include "CServer.h"
#include "CConfiguration.h"
#include "logging/CConsoleLogger.h"
#include "logging/CFileLogger.h"
#include "CRequest.h"
#include "CFile.h"
#include "CStaticFile.h"
#include "CDirectory.h"
#include "CExecutableScript.h"
#include "CError.h"
#include <string>
#include <iostream>
#include <cstring>
#include <thread>
#include <memory>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <filesystem>
#include <arpa/inet.h>
namespace fs = std::filesystem;

using namespace std;

CServer::CServer()
: m_awaitingShutdown(false), m_masterSocket(0), m_maxConnections(10)
{ }

const int CServer::m_bufferSize(4096);

const std::map<std::string, std::string> CServer::m_mimeTypes = {
        {"html", "text/html;charset=utf-8"},
        {"htm","text/html;charset=utf-8"},
        {"jpg","image/jpeg"},
        {"png","image/png"},
        {"svg","image/svg"},
        {"gif","image/gif"},
        {"css","text/css;charset=utf-8"},
        {"js","text/javascript"},
        {"json","application/json"},
        {"xml","text/xml"}
};

bool CServer::Startup(const CConfiguration & config) {
    if (config.m_logType == Console) {
        m_logger = make_shared<CConsoleLogger>(CConsoleLogger());
    }
    else if (config.m_logType == File) {
        m_logger = make_shared<CFileLogger>(CFileLogger(config.m_logFile));
    }

    if (!fs::exists(config.m_serverDirectory) || !fs::is_directory(config.m_serverDirectory)) {
        m_logger->Log("ServerDirectory is not a valid directory");
        return false;
    }
    m_serverDirectory = config.m_serverDirectory;

    m_masterSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (m_masterSocket == 0)
    {
        m_logger->Log("Failed to create a master socket");
        return false;
    }

    m_address.sin_family = config.m_useIPv6 ? AF_INET6 : AF_INET;

    if (!inet_pton(m_address.sin_family, config.m_ipAddress.c_str(), &(m_address.sin_addr))) {
        m_logger->Log("Invalid IP address");
        return false;
    }

    m_address.sin_port = htons( config.m_port );
    memset(m_address.sin_zero, '\0', sizeof m_address.sin_zero);

    return true;
}

int CServer::Listen() {
    const int flag = 1;
    if (setsockopt(m_masterSocket, SOL_SOCKET, SO_REUSEADDR, &flag, sizeof(int)) < 0) {
        m_logger->Log("Setsockopt error");
        exit(EXIT_FAILURE);
    }

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

    char buffer[m_bufferSize] = {0};

    read( socket , buffer, m_bufferSize);
    cout << buffer << endl;

    // Try to parse request and validate it
    CRequest request;
    bool isValid = false;
    auto parseResult = request.TryParseRequest(buffer, &isValid);

    shared_ptr<CFile> file;

    if (!isValid) {
        file = make_shared<CError>(CError(parseResult.second, parseResult.first));
        file->SendResponse(socket);
        close(socket);
        return;
    }

    try {
        string path = MapUriToPath(request.m_uri);
        string contentType = GetContentType(path);

        if (fs::exists(path)) {

            // Directory, it's content should be returned
            if (fs::is_directory(path)) {
                // There should be "/" at the end (maybe redirect)

                // List directory
                file = make_shared<CDirectory>(CDirectory(path));
            }

            // Executable file
            else if (CExecutableScript::IsValidExecutableFile(path)) {
                file = make_shared<CExecutableScript>(CExecutableScript(path));
            }

            // Regular static files (images, JS, CSS, ...)
            else if (fs::is_regular_file(path)) {
                file = make_shared<CStaticFile>(CStaticFile(path));
            }

            // Unsupported
            else {
                throw std::runtime_error("File type not supported");
            }
        }
        else {
            // 404 not found
            throw std::runtime_error("File not found");
        }
    }
    catch (exception & e) {
        // log exception

        file = make_shared<CError>(CError(e.what(), 404));
    }

    file->SendResponse(socket);
    close(socket);
}

string CServer::GetContentType(const string& path) {
    auto pos = path.rfind('.');
    if (pos == std::string::npos)
        return "application/octet-stream";

    string ext = path.substr(pos + 1);

    auto mimeType = m_mimeTypes.find(ext);
    if( mimeType == m_mimeTypes.end() ) {
        return "application/octet-stream";
    } else {
        return mimeType->second;
    }
}

std::string CServer::MapUriToPath(const std::string &rawUri) {
    string uri;

    // Ignore the query because server doesn't implement it
    auto query = rawUri.find('?');
    if (query != string::npos)
        uri = rawUri.substr(0, query);
    else
        uri = rawUri;

    return m_serverDirectory + uri;
}

void CServer::Shutdown() {
    // todo

    m_awaitingShutdown = true;
}
