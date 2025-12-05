#pragma once

#include "auth_controller.hpp"
#include "error_controller.hpp"
#include "health_controller.hpp"

#include <boost/asio/ip/tcp.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <memory>

namespace mail_mcp::http {
    namespace beast = boost::beast;
    namespace http = beast::http;
    namespace asio = boost::asio;
    using tcp = asio::ip::tcp;

    class Session : public std::enable_shared_from_this<Session> {
      public:
        explicit Session(tcp::socket socket, HealthController& healthController,
                         ErrorController& errorController, AuthController& authController);

        // Entry point: start handling this connection
        void start();

      private:
        void doRead();
        void onRequest();
        void onRead(beast::error_code errorCode, std::size_t bytesTransferred);
        void onWrite(beast::error_code errorCode, std::size_t bytesTransferred);

        tcp::socket socket_;
        beast::flat_buffer buffer_;
        http::request<http::string_body> request_;
        http::response<http::string_body> response_;

        // non-owning references; lifetime guaranteed by Server
        // NOLINTNEXTLINE(cppcoreguidelines-avoid-const-or-ref-data-members)
        AuthController& authController_;
        // NOLINTNEXTLINE(cppcoreguidelines-avoid-const-or-ref-data-members)
        HealthController& healthController_;
        // NOLINTNEXTLINE(cppcoreguidelines-avoid-const-or-ref-data-members)
        ErrorController& errorController_;
    };

} // namespace mail_mcp::http