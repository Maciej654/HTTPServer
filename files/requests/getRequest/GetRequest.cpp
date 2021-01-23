//
// Created by maciej on 10.01.2021.
//

#include <unistd.h>
#include "GetRequest.h"

std::string GetRequest::getResponseMessage() {
    std::smatch title_match;
    std::regex_search(json, title_match, json_title_pattern);
    std::string title = title_match.str(1);
    std::stringstream ss;

    if(!containsOneTitle()){
        return AbstractRequest::getInvalidRequest();
    }
    mutexForMap.lock();
    if (!checkIfNoteIsAvailable() ) {
        mutexForMap.unlock();
        return AbstractRequest::getNotFound();
    } else {
        notesMutexes.at(title).lock();
        mutexForMap.unlock();
        std::string body = getResponseBody();
        notesMutexes.at(title).unlock();

        ss << OK_RESPONSE
           << CONTENT_LENGTH
           << body.size()
           << NEW_LINE
           << JSON_TYPE
           << body;
        return ss.str();
    }
}

std::string GetRequest::getResponseBody() {
    std::stringstream ss;
    std::smatch title_match;
    std::smatch content_match;
    std::regex_search(json, title_match, json_title_pattern);

    std::string title = title_match.str(1);
    ss <<
       "\n"
       "{\n"
       "\t\"title\": \"" << title << "\"\n"
                                                  "\t\"content\": \"";
    ss << notes.at(title) << "\"\n}";
    notesMutexes.at(title).unlock();
    return ss.str();

}
