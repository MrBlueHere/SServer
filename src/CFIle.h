/**
* @author Ladislav Floriš
* @date 05.05.20
*/

#pragma once

#include <string>

/// Base virtual class for handling files and which is derived by other classes for specific file types
class CFIle {
public:
    /// Pure virtual function for getting extension for the specific file
    virtual std::string GetExtension() = 0;
};
