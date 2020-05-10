/**
* @author Ladislav Floriš
* @date 10.05.20
*/

#pragma once

#include <string>

class CRequest {
public:
    /// Default constructor
    CRequest() = default;

    /// Default copy constructor
    CRequest(const CRequest &) = default;

    /// Default copy assignment
    CRequest & operator = (const CRequest &) = default;

    /// Default destructor
    ~CRequest() = default;

    /// Parses the request and returns a valid CRequest or throws exception if request doesn't have a correct format
    CRequest ParseRequest(const std::string & rawRequest);

    std::string Method;
    std::string Host;
    std::string Version;
};


