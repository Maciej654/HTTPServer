//
// Created by maciej on 10.01.2021.
//

#include <iostream>
#include "PutRequest.h"

std::string PutRequest::getResponseMessage() {
    std::smatch title_match;
    std::smatch content_match;
    std::regex_search(json, title_match, json_title_pattern);
    std::regex_search(json, content_match, json_content_pattern);

    notes[title_match.str(1)] = content_match.str(1);
    std::string body = getResponseBody();
    std::stringstream  ss;
    ss << "HTTP/1.1 200 OK\n"
          "Content-Length: " << body.size() << "\n"
          "Content-Type: text/html\n"
          << body;
    return ss.str();
}

std::string PutRequest::getResponseBody() {
    return    "\n"
             "<body>\n"
             "<h1>Brace yourself</h1>\n"
             "<h1>This is PUT request</h1>\n"
             "</body>";
}