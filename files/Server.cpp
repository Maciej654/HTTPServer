//
// Created by maciej on 07.01.2021.
//

#include "Server.h"
#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>
#include <thread>
#include <regex>

int threadNum = 0;

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
    threadNum++;
    std::cout << "thread number: " << threadNum << std::endl;
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

     std::smatch title_match;
     std::smatch content_match;
     std::regex_search(body, title_match, json_title_pattern);
     std::regex_search(body, content_match, json_content_pattern);

     std::cout << "TITLE: " << title_match.str(1) << "\n" << "CONTENT: " << content_match.str(1) << "\n";


     std::string msg;

     if (data.rfind("GET", 0) == 0) {
         std::stringstream ss;
         ss << OK_RESPONSE
            << CONTENT_LENGTH
            << "100" //TODO count body
            << "\n"
            << JSON_TYPE
            <<
            "\n"
            "{\n"
            "\t\"title\": \"" << title_match.str(1) << "\"\n"
                                                       "\t\"content\": \"";
         ss << notes.at(title_match.str(1)) << "\"\n}";
         msg = ss.str();
     } else if (data.rfind("PUT", 0) == 0) {
         notes[title_match.str(1)] = content_match.str(1);
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








