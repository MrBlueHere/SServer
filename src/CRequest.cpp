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

    /*if (getline(stream, headerLine)) {
        int position = headerLine.find(' ');
        m_method = headerLine.substr(0, position);

        int positionNext = headerLine.find(' ');
        m_uri = headerLine.substr(position + 1, positionNext);

        m_protocol = headerLine.substr(positionNext + 1, headerLine.length());

        if (m_method != "GET")
            throw runtime_error("Method Not Allowed");
        if (m_protocol != "HTTP/1.1")
            throw runtime_error("Version Not Supported");
    }
    else {
        throw runtime_error("Invalid Request");
    }*/

    if (stream >> m_method >> m_uri >> m_protocol) {
        if (m_method != "GET")
            throw runtime_error("Method Not Allowed");
        if (m_protocol != "HTTP/1.1")
            throw runtime_error("Version Not Supported");
    }
    else {
        throw runtime_error("Invalid Request");
    }

    map<string, string> headers;
    // Read the headers while valid
    while (getline(stream, line)) {
        int position = line.find(':');
        string header = line.substr(0, position);

        string value = line.substr(position + 1, line.length());
        // Trim leading whitespaces
        size_t start = value.find_first_not_of(' ');
        value = (start == string::npos) ? value : value.substr(start);

        // Trim CR char
        size_t end = value.find_last_not_of('\r');
        value = (end == string::npos) ? value : value.substr(start, end);

        headers.insert(pair<string, string>(header, value));
    }

    for (const auto& rec : headers) {
        cout << rec.first << ':' << rec.second << endl;
    }

    /*while(getline(stream, line)){
        cout << line << endl;

        int position = line.find(':');
        string header = line.substr(0, position);
        string value = line.substr(position + 1, line.length());

        // Trim leading whitespaces
        size_t start = value.find_first_not_of(' ');
        value = (start == string::npos) ? value : value.substr(start);

        headers.insert(pair<string, string>(header, value));

        for (const auto& rec : headers) {
            cout << rec.first << ':' << rec.second << endl;
        }
    }*/
}
