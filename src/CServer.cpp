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
#include <string>
#include <iostream>
#include <cstring>
#include <thread>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <filesystem>
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
        m_logger = make_unique<CConsoleLogger>(CConsoleLogger());
    }
    else if (config.m_logType == File) {
        m_logger = make_unique<CFileLogger>(CFileLogger(config.m_logFile));
    }

    m_serverDirectory = config.m_serverDirectory;

    m_masterSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (m_masterSocket == 0)
    {
        m_logger->Log("Failed to create a master socket");
        return false;
    }

    m_address.sin_family = AF_INET;
    m_address.sin_addr.s_addr = config.IpAddressFromString(config.m_ipAddress);
    m_address.sin_port = htons( config.m_port );
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
    char buffer[m_bufferSize] = {0};

    read( socket , buffer, m_bufferSize);
    cout << buffer << endl;

    CRequest request;
    unique_ptr<CFile> file;
    bool responseSent = false;
    try {
        request.ParseRequest(buffer);

        string rawPath = MapUriToPath(request.m_uri);
        fs::path path (rawPath.c_str());
        string contentType = GetContentType(path);

        if (fs::exists(path)) {
            // Directory, it's content should be returned
            if (fs::is_directory(path)) {
                // There should be "/" at the end (maybe redirect)
                // List directory
                cout << "Is dir" << endl;
            }

            // Regular static files (images, JS, CSS, ...)
            else if (fs::is_regular_file(path)) {
                auto size = fs::file_size(path);

                SendResponse(200, socket, "OK", {
                        {"Content-Type", contentType},
                        {"Content-Length", to_string(size)}
                }, false);

                responseSent = true;

                file = make_unique<CStaticFile>(CStaticFile());
                file->SendResponse(socket, path);
                return;
            }

            // Unsupported
            else {
                throw std::runtime_error("File type not supported");
            }
        }
        else {
            // 404 not found
        }
    }
    catch (exception & e) {
        // log exception

        /// TODO: Send 404 or 500
        if (!responseSent) {
            //SendResponse(404,"Not found");
        }

        close(socket);
        return;
    }

    write(socket , hello.c_str(), hello.size());
    cout << "------------------Hello sent-------------------" << endl;
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

void CServer::SendResponse(int code, int socket, const std::string& message, initializer_list<pair<string, string>> headers, bool closeConnection) {
    string buffer;
    auto begin = headers.begin();
    auto end = headers.end();

    //smaz retezec
    buffer.clear();
    buffer.append("HTTP/1.1 ").append(" ");

    //status kod
    buffer.append(to_string(code));

    //status message a enter
    buffer.append(" ").append(message).append("\r\n");

    //projet vsechny hlavicky
    auto x = begin;
    while (x != end) {
        buffer.append(x->first).append(": ").append(x->second).append("\r\n");
        ++x;
    }

    if (closeConnection)
        buffer.append("Connection: close\r\n");

    buffer.append("\r\n");

    write(socket, buffer.c_str(), buffer.size());

    /// TODO: Log
}

void CServer::Shutdown() {
    // todo

    m_awaitingShutdown = true;
}
