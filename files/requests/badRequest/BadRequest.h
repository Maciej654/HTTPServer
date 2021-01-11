//
// Created by maciej on 10.01.2021.
//

#ifndef HTTPSERVER_BADREQUEST_H
#define HTTPSERVER_BADREQUEST_H


#include "../abstractRequest/AbstractRequest.h"

class BadRequest : public AbstractRequest{
public:
    using AbstractRequest::AbstractRequest;
    std::string getResponseMessage() override;
    std::string getResponseBody() override;
};


#endif //HTTPSERVER_BADREQUEST_H
