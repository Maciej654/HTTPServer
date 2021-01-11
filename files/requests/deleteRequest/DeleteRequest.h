//
// Created by maciej on 10.01.2021.
//

#ifndef HTTPSERVER_DELETEREQUEST_H
#define HTTPSERVER_DELETEREQUEST_H


#include <string>
#include "../abstractRequest/AbstractRequest.h"

class DeleteRequest : public AbstractRequest{
public:
    using AbstractRequest::AbstractRequest;
    std::string getResponseMessage() override;
    std::string getResponseBody() override;
};


#endif //HTTPSERVER_DELETEREQUEST_H
