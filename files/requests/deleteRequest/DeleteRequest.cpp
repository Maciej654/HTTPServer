//
// Created by maciej on 10.01.2021.
//

#include "DeleteRequest.h"

std::string DeleteRequest::getResponseMessage() {
    std::stringstream ss;
    std::smatch title_match;
    std::regex_search(json, title_match, json_title_pattern);
    std::string body = getResponseBody();
    if(!containsOneTitle()){
        return AbstractRequest::getInvalidRequest();
    }
    else if (!checkIfNoteIsAvailable()) {
        return AbstractRequest::getNotFound();
    } else {
        notes.erase(title_match.str(1));

        ss << OK_RESPONSE
           << CONTENT_LENGTH
           << body.size()
           << NEW_LINE
           << HTML_TYPE
           << NEW_LINE
           << body;
        return ss.str();
    }
}

std::string DeleteRequest::getResponseBody() {
    return "<body>\n"
           "<h1>Brace yourself</h1>\n"
           "<h1>This is DELETE request</h1>\n"
           "</body>";
}
