#include <server.hpp>

#include <auth_controller.hpp>

#include <boost/asio.hpp>
#include <thread>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <iostream>

void loadServiceEnv(const std::string &filename)
{
    std::ifstream file(filename);

    if (!file)
    {
        throw std::runtime_error(std::string("failed to open service env file: ") + filename);
    };

    std::string line;
    while (std::getline(file, line))
    {
        if (line.empty() || line[0] == '#')
            continue;

        auto pos = line.find('=');
        if (pos == std::string::npos)
            continue;

        std::string key = line.substr(0, pos);
        std::string val = line.substr(pos + 1);

        setenv(key.c_str(), val.c_str(), 1); // overwrite
    }
}

std::string requireEnv(const char *name)
{
    if (const char *value = std::getenv(name))
    {
        return std::string(value);
    }

    throw std::runtime_error(std::string("missing required env var: ") + name);
}

int main(int argc, char* argv[])
{
    try
    {
        namespace asio = boost::asio;
        using tcp = asio::ip::tcp;

        if (argc < 2)
        {
            std::cerr << "Usage: " << argv[0] << " <env_filename>" << std::endl;
            return 1;
        }

        loadServiceEnv(argv[1]);

        mail_mcp::http::GoogleOAuthConfig oauthConfig{
            requireEnv("OAUTH_CLIENT_ID"),
            requireEnv("OAUTH_CLIENT_SECRET"),
            requireEnv("OAUTH_REDIRECT_URI"),
            requireEnv("OAUTH_SCOPE")};

        asio::io_context ioc;

        tcp::endpoint endpoint{tcp::v4(), 8080};
        mail_mcp::http::Server server{ioc, endpoint, oauthConfig};
        server.run(); // starts the async accept chain

        // Run io_context on a small thread pool
        const auto threadCount = std::max(1u, std::thread::hardware_concurrency());
        std::vector<std::thread> threads;
        threads.reserve(threadCount);

        std::cout << "Listening on http://0.0.0.0:8080 with " << threadCount
                  << " worker threads\n";

        for (unsigned i = 0; i < threadCount; ++i)
        {
            threads.emplace_back([&ioc]
                                 { ioc.run(); });
        }

        for (auto &t : threads)
        {
            t.join();
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << "\n";
    }

    return 0;
}