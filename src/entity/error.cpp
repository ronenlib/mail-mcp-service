#include "error.hpp"

#include <nlohmann/json.hpp>
#include <string>
#include <utility>

namespace mail_mcp::entity {

    Error::Error(ErrorCode code, const std::string& message) : code_(code), message_(message) {}

    Error::Error(ErrorCode code, std::string&& message)
        : code_(code), message_(std::move(message)) {}

    auto Error::code() const -> ErrorCode {
        return code_;
    }

    void Error::serialize(nlohmann::json& out) const {
        std::string code;
        stringifyErrorCode(code);

        out = nlohmann::json{{"code", code}, {"message", message_}};
    }

    void Error::stringifyErrorCode(std::string& out) const {
        switch (code_) {
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