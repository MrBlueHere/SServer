/**
* @author Ladislav Floriš
* @date 15.06.20
*/

#pragma once

#include "CFile.h"

class CError : public CFile {
public:
    /// Default constructor
    CError();

    CError(std::string  msg, int code);

    /// Default copy constructor
    CError(const CError &) = default;

    /// Default copy assignment
    CError & operator = (const CError &) = default;

    /// Sends error response (404, 500, etc.) to the given socket
    void SendResponse(int socket) override;

    /// Error message
    std::string m_message;

    /// Status code
    int m_code;
};
