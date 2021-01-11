//
// Created by maciej on 10.01.2021.
//

#ifndef HTTPSERVER_PUTREQUEST_H
#define HTTPSERVER_PUTREQUEST_H


#include "../abstractRequest/AbstractRequest.h"

class PutRequest : public AbstractRequest {
    using AbstractRequest::AbstractRequest;
public:
    std::string getResponseMessage() override;
protected:
    std::string getResponseBody() override;
};


#endif //HTTPSERVER_PUTREQUEST_H
