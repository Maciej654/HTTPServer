//
// Created by maciej on 10.01.2021.
//

#include "GetRequest.h"

std::string GetRequest::getResponseMessage() {
    std::stringstream ss;
    if (!checkIfNoteIsAvailable()) {
        return AbstractRequest::getNotFound();
    } else {
        std::string body = getResponseBody();
        ss << OK_RESPONSE
           << CONTENT_LENGTH << body.size() << "\n"
           << JSON_TYPE
           << body;
        return ss.str();
    }
}

std::string GetRequest::getResponseBody() { //toDo deal with invalid title or whole body
    std::stringstream ss;
    std::smatch title_match;
    std::smatch content_match;
    std::regex_search(json, title_match, json_title_pattern);
    ss <<
       "\n"
       "{\n"
       "\t\"title\": \"" << title_match.str(1) << "\"\n"
                                                  "\t\"content\": \"";
    ss << notes.at(title_match.str(1)) << "\"\n}";
    return ss.str();

}
