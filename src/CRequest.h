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

    /// Constructor accepting the raw request
    explicit CRequest(const std::string & rawRequest);

    /// Default copy constructor
    CRequest(const CRequest &) = default;

    /// Default copy assignment
    CRequest & operator = (const CRequest &) = default;

    /// Default destructor
    ~CRequest() = default;

    /// Parses the request and returns a valid CRequest or throws exception if request doesn't have a correct format
    void ParseRequest(const std::string & rawRequest);

    std::string m_method;
    std::string m_uri;
    std::string m_protocol;
};


