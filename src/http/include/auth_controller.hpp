#pragma once

#include <http_response_data.hpp>

#include <boost/beast/http.hpp>
#include <boost/url/url.hpp>
#include <boost/url/parse.hpp>
#include <memory>
#include <string>

namespace mail_mcp::http {

namespace http = boost::beast::http;
using Request  = http::request<http::string_body>;

using boost::urls::url;

struct GoogleOAuthConfig {
    std::string client_id;
    std::string client_secret;
    std::string redirect_uri;
    std::string scope;  // space-separated scopes
};

class AuthController {
public:
    explicit AuthController(const GoogleOAuthConfig config);

    HttpResponseData oauthStart(const Request& req) const;
    HttpResponseData oauthCallback(const Request& req) const;

private:
    boost::beast::string_view extractCode(boost::beast::string_view target) const;
    const GoogleOAuthConfig config_;
};

} // mail_mcp::http