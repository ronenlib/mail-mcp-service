#pragma once

#include <auth_controller.hpp>
#include <error_controller.hpp>
#include <health_controller.hpp>


#include <boost/asio.hpp>

namespace mail_mcp::http
{

    namespace asio = boost::asio;
    using tcp = asio::ip::tcp;

    class Server
    {
    public:
        Server(asio::io_context &ioc, const tcp::endpoint &endpoint, const GoogleOAuthConfig oauthConfig);

        void run(); // starts server

    private:
        void doAccept();

        asio::io_context &ioc_;
        tcp::acceptor acceptor_;
        ErrorController errorController_;
        HealthController healthController_;
        AuthController authController_;
    };

} // namespace mail_mcp::http