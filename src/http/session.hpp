#pragma once

#include <controller/health_controller.hpp>

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/asio/ip/tcp.hpp>

#include <memory>

namespace mail_mcp::http
{

    namespace beast = boost::beast;
    namespace http = beast::http;
    namespace asio = boost::asio;
    using tcp = asio::ip::tcp;

    class Session : public std::enable_shared_from_this<Session>
    {
    public:
        explicit Session(tcp::socket socket, HealthController& healthController);

        // Entry point: start handling this connection
        void start();

    private:
        void doRead();
        void onRead(beast::error_code ec, std::size_t bytesTransferred);
        void onWrite(beast::error_code ec, std::size_t bytesTransferred);

        tcp::socket socket_;
        beast::flat_buffer buffer_;
        http::request<http::string_body> request_;
        http::response<http::string_body> response_;

        HealthController& healthController_;
    };

} // namespace mail_mcp::http