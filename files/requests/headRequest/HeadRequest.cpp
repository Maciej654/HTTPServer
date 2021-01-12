//
// Created by maciej on 10.01.2021.
//

#include "HeadRequest.h"

std::string HeadRequest::getResponseMessage() {
    std::stringstream ss;
    if (!checkIfNoteIsAvailable()) {
        return AbstractRequest::getNotFound();
    } else {
        std::string body = getResponseBody();
        ss << OK_RESPONSE
           << CONTENT_LENGTH
           << body.size()
           << NEW_LINE
           << JSON_TYPE
           << NEW_LINE;
        return ss.str();
    }
}

std::string HeadRequest::getResponseBody() {
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
