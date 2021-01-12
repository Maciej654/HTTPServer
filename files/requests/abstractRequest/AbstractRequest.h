//
// Created by maciej on 10.01.2021.
//

#ifndef HTTPSERVER_ABSTRACTREQUEST_H
#define HTTPSERVER_ABSTRACTREQUEST_H


#include <string>
#include <regex>
#include <unordered_map>
#include <utility>
#include <sstream>

class AbstractRequest {
public:
    virtual std::string getResponseMessage() = 0;
    AbstractRequest(std::string json, std::unordered_map<std::string, std::string> &notes);

protected:
    std::string json;
    const std::regex json_title_pattern = std::regex("\"title\"[ \t]*:[ \t]*\"([^\"\n]*)\"");
    const std::regex json_content_pattern = std::regex("\"content\"[ \t]*:[ \t]*\"([\\S\\s]*)\"");
    const std::string OK_RESPONSE = "HTTP/1.1 200 OK\n";
    const std::string CONTENT_LENGTH = "Content-Length: ";
    const std::string JSON_TYPE = "Content-Type: application/json\n";
    std::unordered_map<std::string, std::string>& notes;
    virtual std::string getResponseBody() = 0;

};



#endif //HTTPSERVER_ABSTRACTREQUEST_H
