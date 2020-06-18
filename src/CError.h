/**
* @author Ladislav Floriš
* @date 15.06.20
*/

#pragma once

#include "CFile.h"

class CError : public CFile {
public:
    /// Default constructor accepting the logger
    explicit CError(std::shared_ptr<CLogger> logger);

    /// Constructor accepting the error message, code and a logger
    CError(std::string msg, int code, std::shared_ptr<CLogger> logger);

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
