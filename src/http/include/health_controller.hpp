#pragma once

#include <http_response_data.hpp>

#include <string>

namespace mail_mcp::http
{
    class HealthController
    {
    public:
        HealthController() = default;

        HttpResponseData health() const;
    };
}