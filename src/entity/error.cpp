#include <error.hpp>

#include <nlohmann/json.hpp>
#include <string>

namespace mail_mcp::entity
{

    Error::Error(ErrorCode code, const std::string &status)
        : code_(code), message_(std::move(status))
    {
    }

    ErrorCode Error::code() const
    {
        return code_;
    }

    void Error::serialize(nlohmann::json &out) const
    {
        std::string code;
        stringifyErrorCode(code);

        out = nlohmann::json{
            {"code", code},
            {"message", message_}};
    }

    void Error::stringifyErrorCode(std::string &out) const
    {
        switch (code_)
        {
        case ErrorCode::NotFound:
            out = "NOT_FOUND";
            break;
        case ErrorCode::InternalError:
            out = "INTERNAL_ERROR";
            break;
        default:
            out = "UNKNOWN";
        }
    }

} // namespace mail_mcp::entity