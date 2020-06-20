/**
* @author Ladislav Floriš
* @date 13.06.20
*/

#pragma once
#include "CFile.h"

/// Class representing a static file (html, js, css, image, etc.)
class CStaticFile : public CFile {
public:
    /// Default constructor
    CStaticFile() = default;

    /// Constructor accepting a path to the file and a logger
    /// \param path, to the file
    /// \param logger, logger instance
    explicit CStaticFile(std::string path, std::shared_ptr<CLogger> logger);

    /// Default copy constructor
    CStaticFile(const CStaticFile &) = default;

    /// Default copy assignment
    CStaticFile & operator = (const CStaticFile &) = default;

    /// Default destructor
    ~CStaticFile() = default;

    /// Sends a static file response
    void SendResponse(int socket) override;
};


