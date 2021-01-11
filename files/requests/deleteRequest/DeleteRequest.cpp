//
// Created by maciej on 10.01.2021.
//

#include "DeleteRequest.h"

std::string DeleteRequest::getResponseMessage() {
    std::stringstream ss;
    std::smatch title_match;
    std::regex_search(json, title_match, json_title_pattern);
    std::string body = getResponseBody();

    notes.erase(title_match.str(1));

    ss << "HTTP/1.1 200 OK\n"
         << "Content-Length: " << body.size() << "\n"
          "Content-Type: text/html\n"
          "\n"
          << body;
    return ss.str();
}

std::string DeleteRequest::getResponseBody() {
    return  "<body>\n"
            "<h1>Brace yourself</h1>\n"
            "<h1>This is DELETE request</h1>\n"
            "</body>";
}
