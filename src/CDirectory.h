/**
* @author Ladislav Floriš
* @date 10.05.20
*/

#pragma once

#include "CFile.h"

/// Class representing a directory nested inside the server root directory
class CDirectory : public CFile {
public:
    /// Default constructor
    CDirectory() = default;

    /// Constructor accepting a path to the directory and logger
    /// \param path, to the file
    /// \param logger, logger instance
    explicit CDirectory(std::string path, std::shared_ptr<CLogger> logger);

    /// Default copy constructor
    CDirectory(const CDirectory &) = default;

    /// Default copy assignment
    CDirectory & operator = (const CDirectory &) = default;

    /// Default destructor
    ~CDirectory() = default;

    /// Sends a static file response
    /// @param socket, the socket to write to
    void SendResponse(int socket) override;
};


