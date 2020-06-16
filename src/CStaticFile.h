/**
* @author Ladislav Floriš
* @date 13.06.20
*/

#pragma once
#include "CFile.h"

class CStaticFile : public CFile {
public:
    /// Default constructor
    CStaticFile() = default;

    /// Constructor accepting a path to the file
    explicit CStaticFile(std::string path);

    /// Default copy constructor
    CStaticFile(const CStaticFile &) = default;

    /// Default copy assignment
    CStaticFile & operator = (const CStaticFile &) = default;

    /// Sends a static file response
    void SendResponse(int socket) override;
};


