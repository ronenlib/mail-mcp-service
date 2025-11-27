#include <controller/health_controller.hpp>

#include <boost/beast/http.hpp>
#include <string>

namespace beast = boost::beast;

namespace mail_mcp::http
{

    beast::http::response<beast::http::string_body>
    HealthController::handle(const beast::http::request<beast::http::string_body> &req) const
    {
        beast::http::response<beast::http::string_body> res{
            beast::http::status::ok,
            req.version()};

        res.body() = R"({"status":"ok"})";

        return res;
    }
}
