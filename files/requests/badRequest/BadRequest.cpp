//
// Created by maciej on 10.01.2021.
//

#include "BadRequest.h"

std::string BadRequest::getResponseMessage() {
    std::string body = getResponseBody();
    std::stringstream ss;
    ss << "HTTP/1.1 400 Bad Request\n"
       << "Content-Length: " << body.size() - 1 << "\n"
       "Content-Type: text/html\n"
       "\n"
       << body;
    return ss.str();
}

std::string BadRequest::getResponseBody() {
    return "\n"
          "<body>\n"
          "<h1>Bad request</h1>\n"
          "</body>";
}
