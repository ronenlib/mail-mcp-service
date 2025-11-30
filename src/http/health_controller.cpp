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

        HttpResponseData res;
        nlohmann::json payload;
        res.status = beast::http::status::ok;
        res.contentType = CONTENT_TYPE_JSON;

        status.serialize(payload);
        res.body = payload.dump();

        return res;
    }
}
