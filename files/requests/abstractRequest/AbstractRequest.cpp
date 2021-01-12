//
// Created by maciej on 10.01.2021.
//

#include "AbstractRequest.h"

AbstractRequest::AbstractRequest(std::string json, std::unordered_map<std::string, std::string> &notes) : json(
        std::move(
                json)), notes(notes) {}

std::string AbstractRequest::getNotFound() {
    std::string body = "\n"
                       "<body>\n"
                       "<h1>404 Not Found</h1>\n"
                       "</body>";
    std::stringstream ss;
    ss << NOT_FOUND
       << CONTENT_LENGTH
       << body.size() - 1
       << NEW_LINE
       << HTML_TYPE
       << body;
    return ss.str();
}

bool AbstractRequest::checkIfNoteIsAvailable() {
    std::smatch title_match;
    std::regex_search(json, title_match, json_title_pattern);
    return notes.count(title_match.str(1)) != 0;
}
