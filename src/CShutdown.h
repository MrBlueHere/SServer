/**
* @author Ladislav Floriš
* @date 20.06.20
*/

#pragma once

#include "CFile.h"

/// Class handling the shutdown
class CShutdown : public CFile {
public:
    /// Default constructor
    CShutdown() = default;

    /// Constructor accepting logger
    explicit CShutdown(std::shared_ptr<CLogger> logger);

    /// Default copy constructor
    CShutdown(const CShutdown &) = default;

    /// Default copy assignment
    CShutdown & operator = (const CShutdown &) = default;

    /// Sends a static file response
    void SendResponse(int socket) override;
};


