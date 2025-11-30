#include <session.hpp>
#include <health_controller.hpp>
#include <error_controller.hpp>

#include <http_response_data.hpp>

#include <iostream>

namespace mail_mcp::http
{
    Session::Session(tcp::socket socket, HealthController &healthController, ErrorController &errorController)
        : socket_(std::move(socket)), healthController_(healthController), errorController_(errorController)
    {
    }

    void Session::start()
    {
        doRead();
    }

    void Session::doRead()
    {
        auto self = shared_from_this(); // keep Session alive during async operation

        http::async_read(
            socket_,
            buffer_,
            request_,
            [self](beast::error_code ec, std::size_t bytesTransferred)
            {
                self->onRead(ec, bytesTransferred);
            });
    }

    HttpResponseData Session::dispatch()
    {
        if (request_.method() == http::verb::get && request_.target() == "/health")
        {
            return healthController_.health();
        }
        else
        {
            entity::Error error(entity::ErrorCode::NotFound, "path not found");
            return errorController_.error(error);
        }
    }

    void Session::onRead(beast::error_code ec, std::size_t)
    {
        if (ec)
        {
            if (ec != http::error::end_of_stream)
            {
                std::cerr << "Read error: " << ec.message() << "\n";
            }
            return;
        }

        HttpResponseData data = dispatch();

        response_.version(request_.version());
        response_.set(http::field::server, "mail-mcp-server");
        response_.set(http::field::content_type, data.contentType);
        response_.keep_alive(data.keepAlive);
        response_.result(data.status);
        response_.body() = std::move(data.body);
        response_.prepare_payload();

        auto self = shared_from_this();
        http::async_write(
            socket_,
            response_,
            [self](beast::error_code ec, std::size_t bytesTransferred)
            {
                self->onWrite(ec, bytesTransferred);
            });
    }

    void Session::onWrite(beast::error_code ec, std::size_t)
    {
        if (ec)
        {
            std::cerr << "Write error: " << ec.message() << "\n";
            return;
        }

        beast::error_code shutdownEc;
        socket_.shutdown(tcp::socket::shutdown_send, shutdownEc);
    }

} // namespace mail_mcp::http