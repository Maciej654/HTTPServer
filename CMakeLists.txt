cmake_minimum_required(VERSION 3.16)
project(HTTPServer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -pthread")

add_executable(HTTPServer files/main.cpp
        files/Server.cpp
        files/Server.h
        files/requests/abstractRequest/AbstractRequest.cpp
        files/requests/badRequest/BadRequest.cpp
        files/requests/deleteRequest/DeleteRequest.cpp
        files/requests/getRequest/GetRequest.cpp
        files/requests/headRequest/HeadRequest.cpp
        files/requests/putRequest/PutRequest.cpp)