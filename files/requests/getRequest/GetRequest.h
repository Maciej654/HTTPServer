//
// Created by maciej on 10.01.2021.
//

#ifndef HTTPSERVER_GETREQUEST_H
#define HTTPSERVER_GETREQUEST_H


#include <string>
#include "../abstractRequest/AbstractRequest.h"

class GetRequest : public AbstractRequest{
public:
    using AbstractRequest::AbstractRequest;
    std::string getResponseMessage() override;
    std::string getResponseBody() override;
};


#endif //HTTPSERVER_GETREQUEST_H
