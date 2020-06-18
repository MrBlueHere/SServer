/**
* @author Ladislav Floriš
* @date 10.05.20
*/

#include "CDirectory.h"
#include <filesystem>
#include <iostream>
#include <unistd.h>
namespace fs = std::filesystem;

using namespace std;

CDirectory::CDirectory(string path, shared_ptr<CLogger> logger) : CFile(move(path), move(logger))
{ }

void CDirectory::SendResponse(int socket) {
    stringstream oss;

    oss << CFile::HTML_HEADER;
    for (const auto & entry : fs::directory_iterator(m_path))
    {
        string filePath = entry.path();
        size_t found = filePath.find_last_of('/');
        string file;
        if (string::npos != found)
            file = filePath.substr(found + 1, filePath.size());
        oss << "<body>";
        oss << "<a href=\"" << "/" << file.c_str() << "\">" << file << "</a><br/>";
        oss << "</body>";
    }
    oss << CFile::HTML_FOOT;

    SendHeaders(200, socket, "OK", {
            {"Content-Type", CFile::HTML_UTF_8},
            {"Content-Length", to_string(oss.str().size())}
    }, false);

    write(socket, oss.str().c_str(), oss.str().size());
}
