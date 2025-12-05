#pragma once

#include "json_serializable.hpp"

#include <cstdint>
#include <nlohmann/json.hpp>
#include <string>

namespace mail_mcp::entity {
    enum class ErrorCode : std::uint8_t { NotFound, InternalError };

    class Error : public JsonSerializable {
      public:
        Error(ErrorCode code, const std::string& message);
        Error(ErrorCode code, std::string&& message);
        void serialize(nlohmann::json& out) const override;
        [[nodiscard]] auto code() const -> ErrorCode;

      private:
        ErrorCode code_;
        std::string message_;

        void stringifyErrorCode(std::string& out) const;
    };

} // namespace mail_mcp::entity