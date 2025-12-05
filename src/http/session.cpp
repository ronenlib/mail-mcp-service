#include "session.hpp"

#include "auth_controller.hpp"
#include "error_controller.hpp"
#include "health_controller.hpp"
#include "http_response_data.hpp"

#include <iostream>

namespace mail_mcp::http {
    Session::Session(tcp::socket socket, HealthController& healthController,
                     ErrorController& errorController, AuthController& authController)
        : socket_(std::move(socket)), healthController_(healthController),
          errorController_(errorController), authController_(authController) {}

    void Session::start() {
        doRead();
    }

    void Session::doRead() {
        auto self = shared_from_this(); // keep Session alive during async operation

        http::async_read(socket_, buffer_, request_,
                         [self](beast::error_code errorCode, std::size_t bytesTransferred) {
                             self->onRead(errorCode, bytesTransferred);
                         });
    }

    void Session::onRequest() {
        if (request_.method() == http::verb::get && request_.target() == "/health") {
            healthController_.health().applyResponse(response_);
        } else if (request_.method() == http::verb::get &&
                   request_.target() == "/auth/google/start") {
            authController_.oauthStart().applyResponse(response_);
        } else if (request_.method() == http::verb::get &&
                   request_.target() == "/auth/google/callback") {
        } else {
            entity::Error error(entity::ErrorCode::NotFound, "path not found");
            errorController_.error(error).applyResponse(response_);
        }
    }

    void Session::onRead(beast::error_code errorCode, std::size_t) {
        if (errorCode) {
            if (errorCode != http::error::end_of_stream) {
                std::cerr << "Read error: " << errorCode.message() << "\n";
            }
            return;
        }

        onRequest();

        auto self = shared_from_this();
        http::async_write(socket_, response_,
                          [self](beast::error_code errorCode, std::size_t bytesTransferred) {
                              self->onWrite(errorCode, bytesTransferred);
                          });
    }

    void Session::onWrite(beast::error_code errorCode, std::size_t) {
        if (errorCode) {
            std::cerr << "Write error: " << errorCode.message() << "\n";
            return;
        }

        beast::error_code shutdownErrorCode;

        try {
            socket_.shutdown(tcp::socket::shutdown_send);
        } catch (const boost::system::system_error& e) {
            throw std::runtime_error("Server shutdown failed: " + std::string(e.what()));
        }
    }

} // namespace mail_mcp::http