/**
* @author Ladislav Floriš
* @date 05.05.20
*/

#pragma once

#include <string>

/// Abstract Base class responsible for logging, other logger classes are derived from this class
class CLogger {
public:
    /// Pure virtual function for logging
    virtual void Log(const std::string &) = 0;

    /// TODO: Overloads for Log method
};


