cmake_minimum_required(VERSION 3.16)
project(mail_mcp_service LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(src/http)

add_executable(mail_mcp_service
    src/main.cpp
)

target_link_libraries(mail_mcp_service PRIVATE
    mail_mcp_http
)

target_compile_options(mail_mcp_service PRIVATE
    -Wall
    -Wextra
    -Wpedantic
    -Wshadow
    -Wconversion
    -Wsign-conversion
    -fsanitize=address,undefined
    -fno-omit-frame-pointer
)

target_link_options(mail_mcp_service PRIVATE
    -fsanitize=address,undefined
)