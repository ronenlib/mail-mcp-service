#include "error_controller.hpp"

#include "error.hpp"
#include "http_response_data.hpp"

#include <boost/beast/http.hpp>
#include <nlohmann/json.hpp>

namespace mail_mcp::http {
    // NOLINTNEXTLINE(readability-convert-member-functions-to-static)
    auto ErrorController::error(const entity::Error& error) -> HttpResponseData {
        nlohmann::json payload;
        error.serialize(payload);

        return HttpResponseData(payload.dump(), errorCodeToStatus(error.code()));
    }

    auto ErrorController::errorCodeToStatus(entity::ErrorCode code) -> beast::http::status {
        switch (code) {
        case entity::ErrorCode::NotFound:
            return beast::http::status::not_found;
        default:
            return beast::http::status::internal_server_error;
        }
    }
} // namespace mail_mcp::http
