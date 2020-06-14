/**
* @author Ladislav Floriš
* @date 06.05.20
*/

#include "CExecutableScript.h"
#include <sys/stat.h>

using namespace std;

void CExecutableScript::SendResponse(int socket, const string &path) {

}

bool CExecutableScript::IsValidExecutableFile(const string &path) {
    struct stat status{};

    if (stat(path.c_str(), &status) < 0) return false;
    return (status.st_mode & S_IEXEC) != 0;
}
