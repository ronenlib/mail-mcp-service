#pragma once

#include <nlohmann/json.hpp>

namespace mail_mcp::entity {
    class JsonSerializable {
      public:
        JsonSerializable() = default;
        JsonSerializable(const JsonSerializable&) = delete;
        auto operator=(const JsonSerializable&) -> JsonSerializable& = delete;
        JsonSerializable(JsonSerializable&&) = delete;
        auto operator=(JsonSerializable&&) -> JsonSerializable& = delete;
        virtual ~JsonSerializable() = default;
        virtual void serialize(nlohmann::json& out) const = 0;
    };

} // namespace mail_mcp::entity