cmake_minimum_required(VERSION 3.16)
project(HTTPServer)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -pthread")

add_executable(HTTPServer files/main.cpp files/Server.cpp files/Server.h)