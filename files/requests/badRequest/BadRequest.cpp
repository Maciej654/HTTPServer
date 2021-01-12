//
// Created by maciej on 10.01.2021.
//

#include "BadRequest.h"

std::string BadRequest::getResponseMessage() {
    std::string body = getResponseBody();
    std::stringstream ss;
    ss << "HTTP/1.1 405 Method Not Allowed\n"
       << "Content-Length: "
       << body.size() - 1
       << "\n"
       "Content-Type: text/html\n"
       << body;
    return ss.str();
}

std::string BadRequest::getResponseBody() {
    return "\n"
          "<body>\n"
          "<h1>Method Not Allowed</h1>\n"
          "</body>";
}
