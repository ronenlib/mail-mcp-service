#pragma once

#include "http_response_data.hpp"

#include <boost/beast/http.hpp>
#include <error.hpp>

namespace mail_mcp::http {
    namespace beast = boost::beast;

    class ErrorController {
      public:
        ErrorController() = default;

        [[nodiscard]] auto error(const entity::Error& error) -> HttpResponseData;

      private:
        [[nodiscard]] static auto errorCodeToStatus(entity::ErrorCode code) -> beast::http::status;
    };
} // namespace mail_mcp::http