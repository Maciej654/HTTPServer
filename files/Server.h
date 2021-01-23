//
// Created by maciej on 07.01.2021.
//

#ifndef HTTPSERVER_SERVER_H
#define HTTPSERVER_SERVER_H


#include <map>
#include <unordered_map>
#include <regex>

class Server {
public:
    explicit Server(int serverPort);
    void runServer() const;

private:
    const int SERVER_PORT;
    const int QUEUE_SIZE = 5;
    static const int BUFFER_LENGTH = 150;
    inline static const std::regex content_length_pattern = std::regex("Content-Length: ([0-9]+)\r\n");
    inline static std::unordered_map<std::string, std::string> notes;
    inline static std::unordered_map<std::string, std::mutex> notesMutexes;
    static std::mutex mutexForMap;
    static void handleConnection(int socket);
};


#endif //HTTPSERVER_SERVER_H
