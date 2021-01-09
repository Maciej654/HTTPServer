//
// Created by maciej on 07.01.2021.
//

#ifndef HTTPSERVER_SERVER_H
#define HTTPSERVER_SERVER_H


#include <map>

class Server {
public:
    Server(int serverPort);
    void runServer();

private:
    std::map<std::string, std::string> notes;
    const int SERVER_PORT;
    const int QUEUE_SIZE = 5;
    static const int BUFFER_LENGTH = 100;

    static void handleConnection(int socket);
};


#endif //HTTPSERVER_SERVER_H
