#include <error_controller.hpp>
#include <http_response_data.hpp>

#include <error.hpp>

#include <nlohmann/json.hpp>
#include <boost/beast/http.hpp>
#include <string>

namespace beast = boost::beast;

namespace mail_mcp::http
{
    HttpResponseData ErrorController::error(const entity::Error &error) const
    {
        HttpResponseData res;
        nlohmann::json payload;
        res.status = errorCodeToStatus(error.code());
        res.contentType = CONTENT_TYPE_JSON;

        error.serialize(payload);
        res.body = payload.dump();

        return res;
    }

    beast::http::status ErrorController::errorCodeToStatus(entity::ErrorCode code) const
    {
        switch (code)
        {
        case entity::ErrorCode::NotFound:
            return beast::http::status::not_found;
        case entity::ErrorCode::InternalError:
            return beast::http::status::internal_server_error;
        default:
            return beast::http::status::internal_server_error;
        }
    }
}
