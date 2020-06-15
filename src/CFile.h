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
    virtual void SendResponse(int socket) = 0;

    /// Sends response to the given socket
    void SendHeaders(int code, int socket, const std::string& message,
            std::initializer_list<std::pair<std::string, std::string>> headers, bool closeConnection);
};
