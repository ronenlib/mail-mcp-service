#pragma once

#include "json_serializable.hpp"

#include <nlohmann/json.hpp>
#include <string>

namespace mail_mcp::entity {

    class OAuthStart : public JsonSerializable {
      public:
        explicit OAuthStart(const std::string& redirectUrl);
        explicit OAuthStart(std::string&& redirectUrl);
        void serialize(nlohmann::json& out) const override;

      private:
        std::string redirectUrl_;
    };

} // namespace mail_mcp::entity