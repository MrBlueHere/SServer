/**
* @author Ladislav Floriš
* @date 21.06.20
*/

#include <sys/socket.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
#include <cassert>
#include <sstream>
#include "string.h"

using namespace std;

#define PORT 8080
#define IP_ADDR "127.0.0.1"

/// Server should respond with 404 file not found
string testFileNotFound(struct sockaddr_in serverAddr) {
    int sock = 0;
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        cout << "Socket creation failed" << endl;
        return "Error";
    }
    if (connect(sock, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0)
    {
        cout << "Connection Failed" << endl;
        return "Error";
    }

    char buffer[1024] = {0};
    const string msg = "GET /not_existing_path_98798 HTTP/1.1\r\n"
                       "Host: localhost:8080\n"
                       "Connection: keep-alive\n"
                       "Pragma: no-cache\n"
                       "Cache-Control: no-cache\n"
                       "Upgrade-Insecure-Requests: 1\n"
                       "User-Agent: Test\n"
                       "Accept-Encoding: gzip, deflate, br\n"
                       "Accept-Language: en-US,en;q=0.9";

    send(sock, msg.c_str(), msg.size(), 0);
    read(sock , buffer, 1024);
    return buffer;
}

/// Server should respond with 505 HTTP version not supported
string testInvalidVersion(struct sockaddr_in serverAddr) {
    int sock = 0;
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        cout << "Socket creation failed" << endl;
        return "Error";
    }
    if (connect(sock, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0)
    {
        cout << "Connection Failed" << endl;
        return "Error";
    }

    char buffer[1024] = {0};
    const string msg = "GET / HTTP/1.0\r\n"
                       "Host: localhost:8080\n"
                       "Connection: keep-alive\n"
                       "Pragma: no-cache\n"
                       "Cache-Control: no-cache\n"
                       "Upgrade-Insecure-Requests: 1\n"
                       "User-Agent: Test\n"
                       "Accept-Encoding: gzip, deflate, br\n"
                       "Accept-Language: en-US,en;q=0.9";

    send(sock, msg.c_str(), msg.size(), 0);
    read(sock , buffer, 1024);
    return buffer;
}

/// Server should respond with 400 invalid request
/// (has an invalid header line)
string testInvalidRequest(struct sockaddr_in serverAddr) {
    int sock = 0;
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        cout << "Socket creation failed" << endl;
        return "Error";
    }
    if (connect(sock, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0)
    {
        cout << "Connection Failed" << endl;
        return "Error";
    }

    char buffer[1024] = {0};
    const string msg = "GET HTTP/1.1\r\n"
                       "Host: localhost:8080\n"
                       "Connection: keep-alive\n"
                       "Pragma: no-cache\n"
                       "Cache-Control: no-cache\n"
                       "Upgrade-Insecure-Requests: 1\n"
                       "User-Agent: Test\n"
                       "Accept-Encoding: gzip, deflate, br\n"
                       "Accept-Language: en-US,en;q=0.9";

    send(sock, msg.c_str(), msg.size(), 0);
    read(sock , buffer, 1024);
    return buffer;
}

/// Server should respond with 405 method not allowed
string testInvalidMethod(struct sockaddr_in serverAddr) {
    int sock = 0;
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        cout << "Socket creation failed" << endl;
        return "Error";
    }
    if (connect(sock, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0)
    {
        cout << "Connection Failed" << endl;
        return "Error";
    }

    char buffer[1024] = {0};
    const string msg = "DELETE / HTTP/1.1\r\n"
                       "Host: localhost:8080\n"
                       "Connection: keep-alive\n"
                       "Pragma: no-cache\n"
                       "Cache-Control: no-cache\n"
                       "Upgrade-Insecure-Requests: 1\n"
                       "User-Agent: Test\n"
                       "Accept-Encoding: gzip, deflate, br\n"
                       "Accept-Language: en-US,en;q=0.9";

    send(sock, msg.c_str(), msg.size(), 0);
    read(sock , buffer, 1024);
    return buffer;
}

int main(int argc, char **argv) {
    struct sockaddr_in serverAddr;

    memset(&serverAddr, '0', sizeof(serverAddr));

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);

    if(inet_pton(AF_INET, IP_ADDR, &serverAddr.sin_addr) <= 0)
    {
        cout << "Invalid address" << endl;
        return 1;
    }

    // Run tests
    string version;
    int code;
    istringstream stream;

    stream.str(testFileNotFound(serverAddr));
    assert( ( stream >> version >> code ) && code == 404 );
    cout << "Passed testFileNotFound" << endl;

    stream.str(testInvalidVersion(serverAddr));
    assert( ( stream >> version >> code ) && code == 505 );
    cout << "Passed testInvalidVersion" << endl;

    stream.str(testInvalidRequest(serverAddr));
    assert( ( stream >> version >> code) && code == 400 );
    cout << "Passed testInvalidRequest" << endl;

    stream.str(testInvalidMethod(serverAddr));
    assert( ( stream >> version >> code) && code == 405 );
    cout << "Passed testInvalidMethod" << endl;

    return 0;
}