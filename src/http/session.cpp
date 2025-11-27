#include <iostream>

#include <session.hpp>

namespace mail_mcp::http {

Session::Session(tcp::socket socket, HealthController& healthController)
    : socket_(std::move(socket)), healthController_(healthController)
{
}

void Session::start() {
    doRead();
}

void Session::doRead() {
    auto self = shared_from_this(); // keep Session alive during async operation

    http::async_read(
        socket_,
        buffer_,
        request_,
        [self](beast::error_code ec, std::size_t bytesTransferred) {
            self->onRead(ec, bytesTransferred);
        }
    );
}

void Session::onRead(beast::error_code ec, std::size_t) {
    if (ec) {
        if (ec != http::error::end_of_stream) {
            std::cerr << "Read error: " << ec.message() << "\n";
        }
        return;
    }

    if (request_.method() == http::verb::get &&
        request_.target() == "/health") {
        response_ = healthController_.handle(request_);
    } else {
        response_.result(http::status::not_found);
        response_.set(http::field::content_type, "text/plain");
        response_.body() = "Not Found";
    }

    response_.set(http::field::server, "mcp-email-summarizer");
    response_.set(http::field::content_type, "application/json");
    response_.version(request_.version());
    response_.keep_alive(request_.keep_alive());
    response_.prepare_payload();

    auto self = shared_from_this();
    http::async_write(
        socket_,
        response_,
        [self](beast::error_code ec, std::size_t bytesTransferred) {
            self->onWrite(ec, bytesTransferred);
        }
    );
}

void Session::onWrite(beast::error_code ec, std::size_t) {
    if (ec) {
        std::cerr << "Write error: " << ec.message() << "\n";
        return;
    }

    beast::error_code shutdownEc;
    socket_.shutdown(tcp::socket::shutdown_send, shutdownEc);
}

} // namespace mail_mcp::http