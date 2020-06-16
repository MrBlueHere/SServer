/**
* @author Ladislav Floriš
* @date 06.05.20
*/

#pragma once
#include "CFile.h"

/// Class for executable files responsible for managing and executing the executables
class CExecutableScript : public CFile {
public:
    /// Default constructor
    CExecutableScript() = default;

    /// Constructor accepting a path to the file
    explicit CExecutableScript(std::string path);

    /// Default copy constructor
    CExecutableScript(const CExecutableScript &) = default;

    /// Default copy assignment
    CExecutableScript & operator = (const CExecutableScript &) = default;

    /// Sends a static file response
    void SendResponse(int socket) override;

    /// Checks if file specified by the path is executable
    static bool IsValidExecutableFile(const std::string &path);
};


