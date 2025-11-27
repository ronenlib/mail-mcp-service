#pragma once

#include <boost/beast/http.hpp>
#include <string>

namespace beast = boost::beast;

namespace mail_mcp::http
{
    class HealthController
    {
    public:
        HealthController() = default;

        beast::http::response<beast::http::string_body>
        handle(const beast::http::request<beast::http::string_body> &req) const;
    };
}