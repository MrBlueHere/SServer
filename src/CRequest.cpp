/**
* @author Ladislav Floriš
* @date 10.05.20
*/

#include "CRequest.h"
#include <string>
#include <sstream>
#include <iostream>
#include <map>

using namespace std;


pair<int, string> CRequest::TryParseRequest(const string &rawRequest, bool * isValid) noexcept {
    size_t lineEnd = rawRequest.find("\r\n");
    if (lineEnd == string::npos)
    {
        *isValid = false;
        return pair<int, string>(400, "Invalid Request");
    }

    istringstream stream;
    stream.str(rawRequest.substr(0, lineEnd));

    if (!(stream >> m_method >> m_uri >> m_protocol) || m_method.empty() || m_uri.empty() || m_protocol.empty()) {
        *isValid = false;
        return pair<int, string>(400, "Invalid Request");
    }

    if (m_method != "GET") {
        *isValid = false;
        return pair<int, string>(405, "Method Not Allowed");
    }
    if (m_protocol != "HTTP/1.1") {
        *isValid = false;
        return pair<int, string>(505, "HTTP Version Not Supported");
    }

    *isValid = true;
    m_rawRequest = rawRequest;
    return pair<int, string>(200, "OK");
}

std::string CRequest::ToString(bool headOnly = false) {
   if (headOnly) {
       stringstream oss;
       oss << m_method << " " << m_uri << " " << m_protocol;
       return oss.str();
   }

   // The whole request
   return m_rawRequest;
}
