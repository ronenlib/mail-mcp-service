#pragma once

#include <nlohmann/json.hpp>
#include <string>

namespace mail_mcp::entity
{
    enum class ErrorCode
    {
        NotFound,
        InternalError
    };

    class Error
    {
    public:
        Error(ErrorCode code, const std::string &message);
        void serialize(nlohmann::json &out) const;
        ErrorCode code() const;

    private:
        ErrorCode code_;
        std::string message_;

        void stringifyErrorCode(std::string &out) const;
    };

} // namespace mail_mcp::entity