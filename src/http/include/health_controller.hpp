#pragma once

#include "http_response_data.hpp"

namespace mail_mcp::http {
    class HealthController {
      public:
        HealthController() = default;

        [[nodiscard]] auto health() -> HttpResponseData;
    };
} // namespace mail_mcp::http