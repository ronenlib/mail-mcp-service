#include <server.hpp>

#include <boost/asio.hpp>
#include <thread>
#include <vector>
#include <iostream>

int main() {
    try {
        namespace asio = boost::asio;
        using tcp = asio::ip::tcp;

        asio::io_context ioc;

        tcp::endpoint endpoint{tcp::v4(), 8080};
        mail_mcp::http::Server server{ioc, endpoint};
        server.run(); // starts the async accept chain

        // Run io_context on a small thread pool
        const auto threadCount = std::max(1u, std::thread::hardware_concurrency());
        std::vector<std::thread> threads;
        threads.reserve(threadCount);

        std::cout << "Listening on http://0.0.0.0:8080 with " << threadCount
                  << " worker threads\n";

        for (unsigned i = 0; i < threadCount; ++i) {
            threads.emplace_back([&ioc] {
                ioc.run();
            });
        }

        for (auto& t : threads) {
            t.join();
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }

    return 0;
}