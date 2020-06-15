/**
* @author Ladislav Floriš
* @date 05.05.20
*/

#include "CFile.h"
#include <unistd.h>

using namespace std;


void CFile::SendHeaders(int code, int socket, const std::string& message, initializer_list<pair<string, string>> headers, bool closeConnection) {
    string buffer;
    auto begin = headers.begin();
    auto end = headers.end();

    buffer.append("HTTP/1.1 ");
    buffer.append(to_string(code));

    buffer.append(" ").append(message).append("\r\n");

    auto header = begin;
    while (header != end) {
        buffer.append(header->first).append(": ").append(header->second).append("\r\n");
        ++header;
    }

    if (closeConnection)
        buffer.append("Connection: close\r\n");

    buffer.append("\r\n");

    write(socket, buffer.c_str(), buffer.size());

    /// TODO: Log
}
