find_package(nlohmann_json REQUIRED)

add_library(mail_mcp_entity STATIC
    oauth_start.cpp    
    error.cpp
    health_status.cpp
)

target_include_directories(mail_mcp_entity PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)