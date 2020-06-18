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
    /// or isn't supported
    std::pair<int, std::string> TryParseRequest(const std::string & rawRequest, bool * isValid) noexcept;

    /// Returns the string representation of the request
    std::string ToString(bool headOnly);

    /// The http method (GET / POST / PUT, ...)
    std::string m_method;

    /// Requested uri
    std::string m_uri;

    /// Used protocol
    std::string m_protocol;

    /// Original raw request
    std::string m_rawRequest;
};


