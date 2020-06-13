/**
* @author Ladislav Floriš
* @date 13.06.20
*/

#include "CStaticFile.h"
#include <experimental/filesystem>
#include <sys/sendfile.h>

using namespace std;

/// Sends response using sendfile() system call to avoid copying
void CStaticFile::SendResponse(int socket, const string & path) {
    int size = experimental::filesystem::file_size(path);

    int posix_handle = fileno(::fopen(path.c_str(), "r"));

    while (size) {
        auto r = sendfile(socket, posix_handle, nullptr, size);
        if (r < 1) {
            throw runtime_error("sendfile failed");
        }
        size-=r;
    }
}
