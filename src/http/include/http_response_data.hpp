#pragma once

#include "json_serializable.hpp"
#include <boost/beast/http.hpp>
#include <string>

namespace mail_mcp::http {
    namespace beast = boost::beast;
    using Response = beast::http::response<beast::http::string_body>;

    inline constexpr auto SERVICE_VERSION = 1.0;
    inline constexpr auto SERVICE_NAME = "mail-mcp-server";
    inline constexpr auto CONTENT_TYPE_JSON = "application/json; charset=utf-8";
    inline constexpr auto CONTENT_TYPE_PLAIN_TEXT = "text/plain; charset=utf-8";

    class HttpResponseData {
      public:
        explicit HttpResponseData(std::string body,
                                  beast::http::status status = beast::http::status::ok,
                                  std::string contentType = CONTENT_TYPE_JSON,
                                  bool keepAlive = false);

        explicit HttpResponseData(const entity::JsonSerializable& entity,
                                  beast::http::status status = beast::http::status::ok,
                                  bool keepAlive = false);

        void applyResponse(Response& res) const;

      private:
        static auto jsonSerialize(const entity::JsonSerializable& entity) -> std::string;

        beast::http::status status_;
        std::string contentType_;
        std::string body_;
        bool keepAlive_;
    };

} // namespace mail_mcp::http