#pragma once

#include <nlohmann/json.hpp>
#include <string>

namespace mail_mcp::entity
{

    class OAuthStart
    {
    public:
        OAuthStart(const std::string &redirectUrl);
        void serialize(nlohmann::json &out) const;

    private:
        std::string redirectUrl_;
    };

} // namespace mail_mcp::entity