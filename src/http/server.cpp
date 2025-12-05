#include "server.hpp"

#include "auth_controller.hpp"
#include "session.hpp"

#include <boost/beast/core.hpp>
#include <iostream>

namespace mail_mcp::http {
    Server::Server(asio::io_context& ioc, const tcp::endpoint& endpoint,
                   const GoogleOAuthConfig& oauthConfig)
        : ioc_(ioc), acceptor_(ioc), authController_(oauthConfig) {
        try {
            acceptor_.open(endpoint.protocol());
            acceptor_.set_option(asio::socket_base::reuse_address(true));
            acceptor_.bind(endpoint);
            acceptor_.listen(asio::socket_base::max_listen_connections);
        } catch (const boost::system::system_error& e) {
            throw std::runtime_error("Server init failed: " + std::string(e.what()));
        }
    }

    void Server::run() {
        doAccept();
    }

    void Server::doAccept() {
        acceptor_.async_accept([this](boost::system::error_code code, tcp::socket socket) {
            if (!code) {
                std::make_shared<Session>(std::move(socket), healthController_, errorController_,
                                          authController_)
                    ->start();
            } else {
                std::cerr << "Accept error: " << code.message() << "\n";
            }

            // Always accept the next connection
            doAccept();
        });
    }
} // namespace mail_mcp::http