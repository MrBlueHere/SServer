/**
* @author Ladislav Floriš
* @date 15.06.20
*/

#include "CError.h"
#include <unistd.h>
#include <string>
#include <iostream>
#include <sstream>

using namespace std;

CError::CError() : m_message("Not Found"), m_code(404)
{ }

CError::CError(string msg, int code) : m_message(move(msg)), m_code(code)
{ }

void CError::SendResponse(int socket) {
    // Send headers
    SendHeaders(m_code, socket, m_message, {
            {"Content-Type", CFile::HTML_UTF_8},
            {"Allow","GET"}},true);

    ostringstream output;
    output << CFile::HTML_HEADER;
    output
            << "<body>"
            <<"<h1>" << m_code << " " << m_message << "</h1><hr>"
            <<"<p>Powered by SServer written by Ladislav Floriš.</p>"
            << "</body>";
    output << CFile::HTML_FOOT;

    write(socket, output.str().c_str(), output.str().size());
}




