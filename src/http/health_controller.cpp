#include <health_controller.hpp>
#include <http_response_data.hpp>

#include <health_status.hpp>

#include <nlohmann/json.hpp>
#include <boost/beast/http.hpp>
#include <string>

namespace beast = boost::beast;

namespace mail_mcp::http
{

    HttpResponseData HealthController::health() const
    {
        entity::HealthStatus status{"ok"};
        nlohmann::json payload;
        status.serialize(payload);

        return HttpResponseData (payload.dump());
    }
}
