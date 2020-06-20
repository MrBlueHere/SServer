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
    istringstream stream;
    stream.str(rawRequest);

    if (!(stream >> m_method >> m_uri >> m_protocol)) {
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
