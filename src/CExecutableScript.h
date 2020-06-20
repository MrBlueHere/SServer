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
    /// \param path, to the file
    /// \param logger, logger instance
    explicit CExecutableScript(std::string path, std::shared_ptr<CLogger> logger);

    /// Default copy constructor
    CExecutableScript(const CExecutableScript &) = default;

    /// Default copy assignment
    CExecutableScript & operator = (const CExecutableScript &) = default;

    /// Default destructor
    ~CExecutableScript() = default;

    /// Sends a static file response
    /// @param socket, the socket to write to
    void SendResponse(int socket) override;

    /// Checks if file specified by the path is executable
    /// @param path, the file to check
    static bool IsValidExecutableFile(const std::string &path);

private:
    /// Buffer constant
    static const int READ_BUFFER;

    /// Executes the file and returns the read content or an error message and success flag set to false if execution failed
    std::string TryExecute(bool * success);

    /// Sends response for a failed file execution
    void SendFailedResponse(int socket, const std::string & msg);

    /// Send response for a successful file execution
    void SendSuccessResponse(int socket, const std::string & msg);
};


