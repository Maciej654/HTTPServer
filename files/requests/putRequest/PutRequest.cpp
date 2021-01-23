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
    std::string title = title_match.str(1);
    std::string content = content_match.str(1);

    if(!containsOneTitle() || !containsOneContent()){
        return AbstractRequest::getInvalidRequest();
    }
    mutexForMap.lock();
    notesMutexes[title].lock();
    notes[title_match.str(1)] = content_match.str(1);
    mutexForMap.unlock();
    notesMutexes[title].unlock();

    std::string body = getResponseBody();
    std::stringstream ss;
    ss << OK_RESPONSE
       << CONTENT_LENGTH
       << body.size()
       << NEW_LINE
       << HTML_TYPE
       << body;
    return ss.str();
}

std::string PutRequest::getResponseBody() {
    return "\n"
           "<body>\n"
           "<h1>Note has been added correctly</h1>\n"
           "</body>";
}
