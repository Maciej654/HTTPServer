//
// Created by maciej on 07.01.2021.
//

#include "Server.h"
#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <cstring>
#include <thread>

int threadNum = 0;

Server::Server(const int serverPort) : SERVER_PORT(serverPort){}

void Server::runServer() {
    int nSocket, nClientSocket;
    int nBind, nListen;
    int nFoo = 1;
    std::map<std::string, std::string> notes;
    socklen_t nTmp;
    sockaddr_in stAddr{}, stClientAddr{};


    memset(&stAddr, 0, sizeof(sockaddr));
    stAddr.sin_family = AF_INET;
    stAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    stAddr.sin_port = htons(SERVER_PORT);

    /* create a socket */
    nSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (nSocket < 0) {
        fprintf(stderr, "Can't create a socket.\n");
        exit(1);
    }
    setsockopt(nSocket, SOL_SOCKET, SO_REUSEADDR, (char *) &nFoo, sizeof(nFoo));

    /* bind a name to a socket */
    nBind = bind(nSocket, (sockaddr *) &stAddr, sizeof(sockaddr));
    if (nBind < 0) {
        fprintf(stderr, "Can't bind a name to a socket.\n");
        exit(1);
    }
    /* specify queue size */
    nListen = listen(nSocket, QUEUE_SIZE);
    if (nListen < 0) {
        fprintf(stderr, "Can't set queue size.\n");
    }
    while(true)
    {
        nTmp = sizeof(sockaddr);
        nClientSocket = accept(nSocket, (sockaddr *) &stClientAddr, &nTmp);
        if (nClientSocket < 0) {
            fprintf(stderr, "Can't create a connection's socket.\n");
            exit(1);
        }
        std::thread t(handleConnection, nClientSocket);
        t.detach();
    }

}

 void Server::handleConnection(int socket) {
    threadNum++;
    std::cout << "thread number: " << threadNum << std::endl;
    int len = 0;
    do {
        ioctl(socket, FIONREAD, &len);
    } while (len < 1);


    char buffer[BUFFER_LENGTH];
    std::string data;
    while (len > 0) {
        len -= read(socket, buffer, BUFFER_LENGTH);
        data.append(buffer);
        memset(buffer, 0, sizeof(buffer));
    }

    std::cout << data << "\n\n";
    std::string msg;

    if (data.rfind("GET", 0) == 0) {
        msg = "HTTP/1.1 200 OK\n"
              "Content-Length: 100\n"
              "Content-Type: text/html\n"
              "\n"
              "<body>\n"
              "<h1>Brace yourself</h1>\n"
              "<h1>This is GET request</h1>\n"
              "</body>";
    } else if (data.rfind("PUT", 0) == 0) {
        msg = "HTTP/1.1 200 OK\n"
              "Content-Length: 100\n"
              "Content-Type: text/html\n"
              "\n"
              "<body>\n"
              "<h1>Brace yourself</h1>\n"
              "<h1>This is PUT request</h1>\n"
              "</body>";
    } else if (data.rfind("DELETE", 0) == 0) {
        msg = "HTTP/1.1 200 OK\n"
              "Content-Length: 100\n"
              "Content-Type: text/html\n"
              "\n"
              "<body>\n"
              "<h1>Brace yourself</h1>\n"
              "<h1>This is DELETE request</h1>\n"
              "</body>";
    } else if (data.rfind("HEAD", 0) == 0) {
        msg = "HTTP/1.1 200 OK\n"
              "Content-Length: 0\n"
              "Content-Type: application/json\n\n";
    } else {
        msg = "HTTP/1.1 400 Bad Request\n"
              "Content-Length: 100\n"
              "Content-Type: text/html\n"
              "\n"
              "<body>\n"
              "<h1>Bad request</h1>\n"
              "</body>";
    }

    write(socket, msg.c_str(), msg.size());

    close(socket);
}







