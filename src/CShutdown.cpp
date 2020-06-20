/**
* @author Ladislav Floriš
* @date 20.06.20
*/

#include "CShutdown.h"
#include <unistd.h>
#include <sstream>

using namespace std;

CShutdown::CShutdown(shared_ptr<CLogger> logger) : CFile(move(logger))
{ }

void CShutdown::SendResponse(int socket) {
    // Send headers
    SendHeaders(200, socket, "Server shutting down", {
            {"Content-Type", CFile::HTML_UTF_8},
            {"Allow","GET"}},true);

    ostringstream output;
    output << CFile::HTML_HEADER;
    output
            << "<body>"
            <<"<h1>Server shutting down</h1><hr>"
            <<"<p>Powered by SServer written by Ladislav Floriš.</p>"
            << "</body>";
    output << CFile::HTML_FOOT;

    write(socket, output.str().c_str(), output.str().size());
}
