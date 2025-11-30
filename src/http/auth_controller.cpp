#include <auth_controller.hpp>

#include <http_response_data.hpp>
#include <oauth_start.hpp>

#include <nlohmann/json.hpp>
#include <boost/beast/http.hpp>
#include <boost/url/url.hpp>
#include <boost/url/parse.hpp>

#include <memory>
#include <string>

namespace urls = boost::urls;

namespace mail_mcp::http
{
    AuthController::AuthController(GoogleOAuthConfig config)
        : config_(std::move(config)) {}

    HttpResponseData AuthController::oauthStart(const Request &req) const
    {
        urls::url u("https://accounts.google.com/o/oauth2/v2/auth");
        auto params = u.params();

        u.params().append({{"client_id", config_.client_id},
                           {"redirect_uri", config_.redirect_uri},
                           {"response_type", "code"},
                           {"scope", config_.scope},
                           {"access_type", "offline"},
                           {"include_granted_scopes", "true"},
                           {"prompt", "select_account"}});

        entity::OAuthStart oauthStart(u.buffer());
        nlohmann::json payload;
        oauthStart.serialize(payload);

        return HttpResponseData(payload.dump());
    }

    HttpResponseData AuthController::oauthCallback(const Request &req) const
    {
        boost::beast::string_view code = extractCode(req.target());

        // If there's no "code" param, something went wrong
        if (code.empty())
        {
            // throw
        }

        // TODO:
        // 1. Validate `state` against what you generated in oauthStart().
        // 2. Exchange `code` for tokens at https://oauth2.googleapis.com/token
        //    using config_.client_id, config_.client_secret, config_.redirect_uri.
        // 3. Store access_token / refresh_token somewhere.

        return HttpResponseData("{}");
    }

    boost::beast::string_view AuthController::extractCode(boost::beast::string_view target) const
    {
        urls::url_view parsed = urls::parse_relative_ref(target).value();

        auto params = parsed.params();
        auto it = params.find("code");

        if (it != params.end())
        {
            return (*it).value;
        }

        return {};
    }

} // mail_mcp::http