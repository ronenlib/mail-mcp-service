#include "health_controller.hpp"

#include "health_status.hpp"
#include "http_response_data.hpp"

#include <boost/beast/http.hpp>
#include <nlohmann/json.hpp>
#include <string>

namespace mail_mcp::http {

    // NOLINTNEXTLINE(readability-convert-member-functions-to-static)
    auto HealthController::health() -> HttpResponseData {
        const entity::HealthStatus status{"ok"};
        nlohmann::json payload;
        status.serialize(payload);

        return HttpResponseData(payload.dump());
    }
} // namespace mail_mcp::http
