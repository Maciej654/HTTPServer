//
// Created by maciej on 10.01.2021.
//

#include <iostream>
#include <utility>
#include "AbstractRequest.h"



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
       << HTML_TYPE << NEW_LINE;
    return ss.str();
}

std::string AbstractRequest::getInvalidRequest() {
    std::string body = "\n"
                       "<body>\n"
                       "<h1>400 Bad Request</h1>\n"
                       "</body>";
    std::stringstream ss;
    ss << BAD_REQUEST
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

bool AbstractRequest::containsOneTitle() {
    std::sregex_iterator iter(json.begin(), json.end(), json_title_pattern);
    std::sregex_iterator end;
    int count = 0;
    while(iter != end)
    {
        ++iter;
        ++count;
    }
    return count == 1;
}

bool AbstractRequest::containsOneContent() {
    std::sregex_iterator iter(json.begin(), json.end(), json_content_pattern);
    std::sregex_iterator end;
    int count = 0;
    while(iter != end)
    {
        ++iter;
        ++count;
    }
    return count == 1;
}

AbstractRequest::AbstractRequest(std::string json, std::unordered_map<std::string, std::string> &notes) : json(std::move(
        json)), notes(notes) {}



