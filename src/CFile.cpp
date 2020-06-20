/**
* @author Ladislav Floriš
* @date 05.05.20
*/

#include "CFile.h"
#include "CServer.h"
#include <unistd.h>

#include <utility>

using namespace std;

const char* CFile::HTML_UTF_8 = "text/html;charset=utf-8";

const char * CFile::HTML_HEADER = "<!DOCTYPE html>\n"
                                  "<html lang=\"en\">\n"
                                  "<head>\n"
                                  "    <meta charset=\"UTF-8\">\n"
                                  "    <title>SServer</title>\n"
                                  "</head>";

const char * CFile::HTML_FOOT = "</html>";

CFile::CFile(string path, shared_ptr<CLogger> logger) : m_path(move(path)), m_logger(move(logger))
{ }

CFile::CFile(shared_ptr<CLogger> logger) : m_logger(move(logger))
{ }

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

    if (m_logger->m_headerOnly)
        m_logger->Info(buffer.substr(0, buffer.find("\r\n")));
    else
        m_logger->Info(buffer);
}
