#include <server.hpp>

#include <session.hpp>
#include <auth_controller.hpp>

#include <boost/beast/core.hpp>
#include <iostream>

namespace mail_mcp::http
{
    Server::Server(asio::io_context &ioc, const tcp::endpoint &endpoint, const GoogleOAuthConfig oauthConfig)
        : ioc_(ioc), acceptor_(ioc), authController_(std::move(oauthConfig))
    {
        boost::system::error_code ec;

        acceptor_.open(endpoint.protocol(), ec);
        if (ec)
        {
            throw std::runtime_error("Failed to open acceptor: " + ec.message());
        }

        acceptor_.set_option(asio::socket_base::reuse_address(true), ec);
        if (ec)
        {
            throw std::runtime_error("Failed to set reuse_address: " + ec.message());
        }

        acceptor_.bind(endpoint, ec);
        if (ec)
        {
            throw std::runtime_error("Failed to bind: " + ec.message());
        }

        acceptor_.listen(asio::socket_base::max_listen_connections, ec);
        if (ec)
        {
            throw std::runtime_error("Failed to listen: " + ec.message());
        }
    }

    void Server::run()
    {
        doAccept();
    }

    void Server::doAccept()
    {
        acceptor_.async_accept(
            [this](boost::system::error_code ec, tcp::socket socket)
            {
                if (!ec)
                {
                    std::make_shared<Session>(std::move(socket), healthController_, errorController_, authController_)->start();
                }
                else
                {
                    std::cerr << "Accept error: " << ec.message() << "\n";
                }

                // Always accept the next connection
                doAccept();
            });
    }
} // namespace mail_mcp::http