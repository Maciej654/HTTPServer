//
// Created by maciej on 10.01.2021.
//

#include "AbstractRequest.h"

#include <utility>

AbstractRequest::AbstractRequest(std::string json, std::unordered_map<std::string, std::string> &notes) : json(std::move(
        json)), notes(notes) {}
