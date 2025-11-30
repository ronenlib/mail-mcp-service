#include <health_status.hpp>

#include <nlohmann/json.hpp>
#include <string>

namespace mail_mcp::entity
{

    HealthStatus::HealthStatus(const std::string &status)
        : status_(std::move(status))
    {
    }

    void HealthStatus::serialize(nlohmann::json &out) const
    {
        out = nlohmann::json{
            {"status", status_}};
    }

} // namespace mail_mcp::entity