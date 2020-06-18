/**
* @author Ladislav Floriš
* @date 06.05.20
*/

#include "CExecutableScript.h"
#include "CError.h"
#include <sys/stat.h>
#include <unistd.h>

using namespace std;

const int CExecutableScript::READ_BUFFER = 256;

CExecutableScript::CExecutableScript(string path, shared_ptr<CLogger> logger) : CFile(move(path), move(logger))
{ }

void CExecutableScript::SendResponse(int socket) {
    bool success = false;
    string execResult = TryExecute(&success);

    if (success) {
        SendSuccessResponse(socket, execResult);
        return;
    }
    else {
        string msg = "File execution failed: ";
        SendFailedResponse(socket, msg + execResult);
        return;
    }
}

string CExecutableScript::TryExecute(bool * success) {
    char buffer[READ_BUFFER];
    string result;

    // Try to open the file
    FILE * exec;
    if(!(exec = popen(m_path.c_str(), "r"))) {
        *success = false;
        return "Failed to open the executable file";
    }

    try {
        while(!feof(exec)) {
            if (fgets(buffer, READ_BUFFER, exec) != nullptr)
                result += buffer;
        }
    }
    catch(exception & e) {
        pclose(exec);
        // Todo: Log
        *success = false;
        return e.what();
    }

    if (pclose(exec) == 0) {
        *success = true;
        return result;
    }
    else {
        *success = false;
        return "Failed to close the file";
    }
}

bool CExecutableScript::IsValidExecutableFile(const string &path) {
    struct stat status{};

    if (stat(path.c_str(), &status) < 0) return false;
    return (status.st_mode & S_IEXEC) != 0;
}

void CExecutableScript::SendFailedResponse(int socket, const string &fileResult) {
    CError errorResponse(fileResult, 500, m_logger);
    errorResponse.SendResponse(socket);
}

void CExecutableScript::SendSuccessResponse(int socket, const string &fileResult) {
    int size = fileResult.size();

    SendHeaders(200, socket, "OK", {
            {"Content-Type", HTML_UTF_8},
            {"Content-Length", to_string(size)}
    }, false);

    write(socket, fileResult.c_str(), size);
}
