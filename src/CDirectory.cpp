/**
* @author Ladislav Floriš
* @date 10.05.20
*/

#include "CDirectory.h"

#include <utility>

using namespace std;

CDirectory::CDirectory(string path) : CFile(move(path))
{ }

void CDirectory::SendResponse(int socket) {
    for (const auto & entry : fs::directory_iterator(path))
        std::cout << entry.path() << std::endl;
}
