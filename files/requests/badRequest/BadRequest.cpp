//
// Created by maciej on 10.01.2021.
//

#include "BadRequest.h"

std::string BadRequest::getResponseMessage() {
    std::string body = getResponseBody();
    std::stringstream ss;
    ss << NOT_ALLOWED
       << CONTENT_LENGTH
       << body.size() - 1
       << "\n"
       << HTML_TYPE
       << body;
    return ss.str();
}

std::string BadRequest::getResponseBody() {
    return "\n"
          "<body>\n"
          "<h1>Method Not Allowed</h1>\n"
          "</body>";
}
