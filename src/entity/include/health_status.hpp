#pragma once

#include "json_serializable.hpp"

#include <nlohmann/json.hpp>
#include <string>

namespace mail_mcp::entity {

    class HealthStatus : public JsonSerializable {
      public:
        explicit HealthStatus(const std::string& status);
        explicit HealthStatus(std::string&& status);
        void serialize(nlohmann::json& out) const override;

      private:
        std::string status_;
    };

} // namespace mail_mcp::entity