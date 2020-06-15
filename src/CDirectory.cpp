/**
* @author Ladislav Floriš
* @date 10.05.20
*/

#include "CDirectory.h"

#include <utility>

using namespace std;

CDirectory::CDirectory(string path) : m_path(std::move(path))
{ }

void CDirectory::SendResponse(int socket) {

}
