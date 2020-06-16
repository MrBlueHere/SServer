/**
* @author Ladislav Floriš
* @date 06.05.20
*/

#include "CExecutableScript.h"
#include <sys/stat.h>

#include <utility>

using namespace std;

CExecutableScript::CExecutableScript(string path) : CFile(move(path))
{ }

void CExecutableScript::SendResponse(int socket) {

}

bool CExecutableScript::IsValidExecutableFile(const string &path) {
    struct stat status{};

    if (stat(path.c_str(), &status) < 0) return false;
    return (status.st_mode & S_IEXEC) != 0;
}

