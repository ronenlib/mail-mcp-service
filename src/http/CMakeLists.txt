find_package(Boost 1.8 REQUIRED CONFIG COMPONENTS system)

add_library(mail_mcp_http STATIC
    error_controller.cpp    
    health_controller.cpp
    server.cpp
    session.cpp
)

target_link_libraries(mail_mcp_http PRIVATE
    mail_mcp_entity
    Boost::system
)

target_include_directories(mail_mcp_http PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)