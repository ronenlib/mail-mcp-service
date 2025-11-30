#pragma once

#include <boost/beast/http.hpp>
#include <string>

namespace beast = boost::beast;
using Response  = beast::http::response<beast::http::string_body>;

#define SERVICE_VERSION 1.0
#define SERVICE_NAME "mail-mcp-server"
#define CONTENT_TYPE_JSON "application/json; charset=utf-8"
#define CONTENT_TYPE_PLAIN_TEXT "text/plain; charset=utf-8"

namespace mail_mcp::http
{
    class HttpResponseData
    {
    public:
        HttpResponseData(const std::string &body,
            beast::http::status status = beast::http::status::ok, 
            const std::string &contentType = CONTENT_TYPE_JSON, 
            bool keepAlive = false);

        void applyResponse(Response &res) const;

    private:
        beast::http::status status_;
        std::string contentType_;
        std::string body_;
        bool keepAlive_;
    };

} // mail_mcp::http