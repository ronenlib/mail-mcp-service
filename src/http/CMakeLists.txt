find_package(Boost 1.81 REQUIRED CONFIG COMPONENTS system url)

add_library(mail_mcp_http STATIC
    auth_controller.cpp
    error_controller.cpp    
    health_controller.cpp
    http_response_data.cpp
    server.cpp
    session.cpp
)

target_link_libraries(mail_mcp_http PRIVATE
    mail_mcp_entity
    Boost::system
    Boost::url
)

target_include_directories(mail_mcp_http PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)