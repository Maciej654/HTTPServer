#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>
#include <sstream>
#include <map>

#define SERVER_PORT 1234
#define QUEUE_SIZE 5
#define BUFFER_LENGTH 240

int main(int argc, char *argv[]) {
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
        fprintf(stderr, "%s: Can't create a socket.\n", argv[0]);
        exit(1);
    }
    setsockopt(nSocket, SOL_SOCKET, SO_REUSEADDR, (char *) &nFoo, sizeof(nFoo));

    /* bind a name to a socket */
    nBind = bind(nSocket, (sockaddr *) &stAddr, sizeof(sockaddr));
    if (nBind < 0) {
        fprintf(stderr, "%s: Can't bind a name to a socket.\n", argv[0]);
        exit(1);
    }
    /* specify queue size */
    nListen = listen(nSocket, QUEUE_SIZE);
    if (nListen < 0) {
        fprintf(stderr, "%s: Can't set queue size.\n", argv[0]);
    }

    while (true) {
        /* block for connection request */
        nTmp = sizeof(sockaddr);
        nClientSocket = accept(nSocket, (sockaddr *) &stClientAddr, &nTmp);
        if (nClientSocket < 0) {
            fprintf(stderr, "%s: Can't create a connection's socket.\n", argv[0]);
            exit(1);
        }

        printf("%s: [connection from %s]\n", argv[0], inet_ntoa((in_addr) stClientAddr.sin_addr));

        //toDo do something with read!!! Maybe done
        int len = 0;
        do {
            ioctl(nClientSocket, FIONREAD, &len);
        } while (len < 1);

        char buffer[len];
        std::string data = "";
        int f = 0;
        f = read(nClientSocket, buffer, len);
        data.append(buffer);
        memset(buffer, 0, len);

//        do {

//        } while (f == BUFFER_LENGTH);

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
        } else if (data.rfind("HEAD", 0) == 0) { //TODO For some reason HEAD is not working
            msg = "HTTP/1.1 200 OK\n"
                  "Content-Length: 0\n"
                  "Content-Type: application/json";
        } else { //TODO FIX BAD REQUEST
            msg = "HTTP/1.1 400 Bad Request\n"
                  "Content-Length: 100\n"
                  "Content-Type: text/html\n";
        }


        write(nClientSocket, msg.c_str(), msg.size());

        close(nClientSocket);
    }
}
