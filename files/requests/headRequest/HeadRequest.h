//
// Created by maciej on 10.01.2021.
//

#ifndef HTTPSERVER_HEADREQUEST_H
#define HTTPSERVER_HEADREQUEST_H


#include "../abstractRequest/AbstractRequest.h"

class HeadRequest : public AbstractRequest{
    using AbstractRequest::AbstractRequest;
    std::string getResponseMessage() override;
    std::string getResponseBody() override;
};


#endif //HTTPSERVER_HEADREQUEST_H
