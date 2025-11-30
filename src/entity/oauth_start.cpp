#include <oauth_start.hpp>

#include <nlohmann/json.hpp>
#include <string>

namespace mail_mcp::entity
{

    OAuthStart::OAuthStart(const std::string &redirectUrl)
        : redirectUrl_(std::move(redirectUrl))
    {
    }

    void OAuthStart::serialize(nlohmann::json &out) const
    {
        out = nlohmann::json{
            {"redirectUrl", redirectUrl_}};
    }

} // namespace mail_mcp::entity