/**
* @author Ladislav Floriš
* @date 15.06.20
*/

#pragma once

#include "CFile.h"

/// Class for error responses (file not found, etc.)
class CError : public CFile {
public:
    /// Default constructor accepting the logger
    /// \param logger, logger instance
    explicit CError(std::shared_ptr<CLogger> logger);

    /// Constructor accepting the error message, code and a logger
    /// \param msg, error message
    /// \param code, response code (404, 500, etc.)
    /// \param logger, logger instance
    CError(std::string msg, int code, std::shared_ptr<CLogger> logger);

    /// Default copy constructor
    CError(const CError &) = default;

    /// Default copy assignment
    CError & operator = (const CError &) = default;

    /// Default destructor
    ~CError() = default;

    /// Sends error response (404, 500, etc.) to the given socket
    /// @param socket, the socket to write to
    void SendResponse(int socket) override;

    /// Error message
    std::string m_message;

    /// Status code
    int m_code;
};
