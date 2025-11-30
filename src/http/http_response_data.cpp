#include <http_response_data.hpp>

#include <boost/beast/http.hpp>
#include <string>

namespace beast = boost::beast;

namespace mail_mcp::http
{
    HttpResponseData::HttpResponseData(const std::string &body,
        beast::http::status status, 
        const std::string &contentType, 
        bool keepAlive)
        : status_(status), contentType_(contentType), body_(body), keepAlive_(keepAlive) {}

    void HttpResponseData::applyResponse(Response &response) const {
        response.version(SERVICE_VERSION);
        response.set(beast::http::field::server, SERVICE_NAME);
        response.set(beast::http::field::content_type, contentType_);
        response.keep_alive(keepAlive_);
        response.result(status_);
        response.body() = std::move(body_);
        response.prepare_payload();
    }
} // mail_mcp::http