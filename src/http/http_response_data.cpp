#include "http_response_data.hpp"

#include <string>

namespace mail_mcp::http {
    HttpResponseData::HttpResponseData(std::string body, beast::http::status status,
                                       std::string contentType, bool keepAlive)
        : body_(std::move(body)), contentType_(std::move(contentType)), status_(status),
          keepAlive_(keepAlive) {}

    HttpResponseData::HttpResponseData(const entity::JsonSerializable& entity,
                                       beast::http::status status, bool keepAlive)
        : body_(jsonSerialize(entity)), contentType_(CONTENT_TYPE_JSON), status_(status),
          keepAlive_(keepAlive) {}

    auto HttpResponseData::jsonSerialize(const entity::JsonSerializable& entity) -> std::string {
        nlohmann::json payload;
        entity.serialize(payload);
        return payload.dump();
    }

    void HttpResponseData::applyResponse(Response& response) const {
        response.version(SERVICE_VERSION);
        response.set(beast::http::field::server, SERVICE_NAME);
        response.set(beast::http::field::content_type, contentType_);
        response.keep_alive(keepAlive_);
        response.result(status_);
        response.body() = body_;
        response.prepare_payload();
    }
} // namespace mail_mcp::http