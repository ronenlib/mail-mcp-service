#pragma once

#include <controller/health_controller.hpp>

#include <boost/asio.hpp>

namespace mail_mcp::http
{

    namespace asio = boost::asio;
    using tcp = asio::ip::tcp;

    class Server
    {
    public:
        Server(asio::io_context &ioc, const tcp::endpoint &endpoint);

        void run(); // starts async accept

    private:
        void doAccept();

        asio::io_context &ioc_;
        tcp::acceptor acceptor_;
        HealthController healthController_;
    };

} // namespace mail_mcp::http