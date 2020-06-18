/**
* @author Ladislav Floriš
* @date 13.06.20
*/

#include "CStaticFile.h"
#include "CServer.h"
#include <filesystem>
#include <iostream>
#include <utility>
#include <sys/sendfile.h>
#include <unistd.h>

using namespace std;

CStaticFile::CStaticFile(string path, shared_ptr<CLogger> logger) : CFile(move(path), move(logger))
{ }

/// Sends response using sendfile() system call to avoid copying
void CStaticFile::SendResponse(int socket) {
    int size = filesystem::file_size(m_path);
    string contentType = CServer::GetContentType(m_path);

    // Send headers first, so that we start sending data to client asap and then send the file
    SendHeaders(200, socket, "OK", {
            {"Content-Type", contentType},
            {"Content-Length", to_string(size)}
    }, false);

    int posix_handle = fileno(::fopen(m_path.c_str(), "r"));

    if (posix_handle) {
        while (size) {
            auto r = sendfile(socket, posix_handle, nullptr, size);
            if (r < 1) {
                throw runtime_error("Sending static file failed");
            }
            size-=r;
        }
        close(posix_handle);
    }
}
