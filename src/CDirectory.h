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
    explicit CDirectory() = default;

    /// Default copy constructor
    CDirectory(const CDirectory &) = default;

    /// Default copy assignment
    CDirectory & operator = (const CDirectory &) = default;

    /// Sends a static file response
    void SendResponse(int socket, const std::string & path) override;
};


