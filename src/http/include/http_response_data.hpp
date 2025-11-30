#pragma once

#include <boost/beast/http.hpp>
#include <string>

namespace http = boost::beast::http;

#define CONTENT_TYPE_JSON "application/json";

struct HttpResponseData {
    http::status status = http::status::ok;
    std::string contentType = CONTENT_TYPE_JSON;
    std::string body;
    bool keepAlive = false;
};