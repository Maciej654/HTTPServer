//
// Created by maciej on 07.01.2021.
//

#include "Server.h"
#include "requests/getRequest/GetRequest.h"
#include "requests/putRequest/PutRequest.h"
#include "requests/deleteRequest/DeleteRequest.h"
#include "requests/headRequest/HeadRequest.h"
#include "requests/badRequest/BadRequest.h"
#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>
#include <thread>
#include <regex>


Server::Server(const int serverPort) : SERVER_PORT(serverPort){}

void Server::runServer() const {
    int nSocket, nClientSocket;
    int nBind, nListen;
    int nFoo = 1;
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
     if (socket < 0) {
         fprintf(stderr, "Can't create a connection's socket.\n");
         exit(1);
     }

     std::string data;
     int already_read = 0;
     int content_len = -1;
     int position;
     char buffer[BUFFER_LENGTH+1];
     memset(buffer, '\0', BUFFER_LENGTH+1);
     do {
         already_read += read(socket, buffer, BUFFER_LENGTH);
         data.append(buffer);
         memset(buffer, '\0', BUFFER_LENGTH+1);
         std::smatch regex_match;
         if(content_len < 0 && std::regex_search(data, regex_match, content_length_pattern)) {
             content_len = std::stoi(regex_match.str(1));
         }
         position = data.rfind("\r\n\r\n");
     } while(position < 0 || already_read < (content_len + position + 4));
     std::cout << data << "\n\n";

     std::string body = data.substr(position + 4);

     std::string msg;
     AbstractRequest *request;

     if (data.rfind("GET", 0) == 0) {
         request = new GetRequest (body, notes);
     } else if (data.rfind("PUT", 0) == 0) {
         request = new PutRequest (body, notes);
     } else if (data.rfind("DELETE", 0) == 0) {
         request = new DeleteRequest(body,notes);
     } else if (data.rfind("HEAD", 0) == 0) {
        request = new HeadRequest(body, notes);
     } else {
         request = new BadRequest(body, notes);
     }
     msg = request->getResponseMessage();
     write(socket, msg.c_str(), msg.size());

     close(socket);
}








