#pragma once

#include <http_response_data.hpp>

#include <error.hpp>

#include <boost/beast/http.hpp>
#include <string>

namespace beast = boost::beast;

namespace mail_mcp::http
{
    class ErrorController
    {
    public:
        ErrorController() = default;

        HttpResponseData error(const entity::Error &error) const;

    private:
        beast::http::status errorCodeToStatus(entity::ErrorCode code) const;
    };
}