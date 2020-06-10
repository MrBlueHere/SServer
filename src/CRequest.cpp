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


CRequest::CRequest(const string &rawRequest) {
    ParseRequest(rawRequest);
}

void CRequest::ParseRequest(const string &rawRequest) {
    istringstream stream;
    stream.str(rawRequest);
    string line, headerLine;

    if (stream >> m_method >> m_uri >> m_protocol) {
        if (m_method != "GET")
            throw runtime_error("Method Not Allowed");
        if (m_protocol != "HTTP/1.1")
            throw runtime_error("Version Not Supported");
    }
    else {
        throw runtime_error("Invalid Request");
    }

    // Read the headers while valid, but don't process them
    // This server doesn't implement any features specified by headers
    /*do {
        getline(stream, line);
    } while (!line.empty());*/
}
