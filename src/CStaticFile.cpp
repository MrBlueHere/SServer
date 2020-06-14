/**
* @author Ladislav Floriš
* @date 13.06.20
*/

#include "CStaticFile.h"
#include <filesystem>
#include <sys/sendfile.h>
#include <unistd.h>

using namespace std;

/// Sends response using sendfile() system call to avoid copying
void CStaticFile::SendResponse(int socket, const string & path) {
    int size = filesystem::file_size(path);

    int posix_handle = fileno(::fopen(path.c_str(), "r"));

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