/**
* @author Ladislav Floriš
* @date 05.05.20
*/

#pragma once

#include "logging/CLogger.h"
#include <string>
#include <memory>

/// Abstract Base class for handling files and which is derived by other classes for specific file types
class CFile {
public:
    /// Default constructor
    CFile() = default;

    /// Constructor accepting only the logger
    /// \param logger, logger instance
    explicit CFile(std::shared_ptr<CLogger> logger);

    /// Constructor accepting the path to the file and logger
    /// \param path, to the file
    /// \param logger, logger instance
    explicit CFile(std::string path, std::shared_ptr<CLogger> logger);

    /// Pure virtual function responsible for sending the file's content using the given socket
    /// \param socket, the socket to write to
    virtual void SendResponse(int socket) = 0;

    /// Sends response to the given socket
    /// \param code, status code
    /// \param socket, socket to write to
    /// \param message, message to display on the page
    /// \param headers, http headers
    /// \param closeConnection, whether the connection should be closed
    void SendHeaders(int code, int socket, const std::string& message,
            std::initializer_list<std::pair<std::string, std::string>> headers, bool closeConnection);

    /// Path to the file
    std::string m_path;

    /// HTML UTF8 content type content
    static const char* HTML_UTF_8;
    /// HTML header constant
    static const char* HTML_HEADER;
    /// HTML footer constant
    static const char* HTML_FOOT;

protected:
    /// Logger instance
    std::shared_ptr<CLogger> m_logger;
};
