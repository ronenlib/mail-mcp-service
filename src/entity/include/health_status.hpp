#pragma once

#include <nlohmann/json.hpp>
#include <string>

namespace mail_mcp::entity
{

    class HealthStatus
    {
    public:
        HealthStatus(const std::string &status);
        void serialize(nlohmann::json &out) const;

    private:
        std::string status_;
    };

} // namespace mail_mcp::entity