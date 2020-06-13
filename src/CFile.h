/**
* @author Ladislav Floriš
* @date 05.05.20
*/

#pragma once

#include <string>

/// Abstract Base class for handling files and which is derived by other classes for specific file types
class CFile {
public:
    /// Pure virtual function responsible for sending the file's content using the given socket
    virtual void SendResponse(int socket, const std::string & path) = 0;
};
