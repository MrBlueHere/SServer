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

    /// Constructor accepting a path to the directory
    explicit CDirectory(std::string path);

    /// Default copy constructor
    CDirectory(const CDirectory &) = default;

    /// Default copy assignment
    CDirectory & operator = (const CDirectory &) = default;

    /// Sends a static file response
    void SendResponse(int socket) override;

    /// Path to the file
    std::string m_path;
};


