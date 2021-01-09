#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>
#include <map>
#include <sstream>
#include <iterator>
#include <regex>
#include <unordered_map>

#define SERVER_PORT 1234
#define QUEUE_SIZE 5
#define BUFFER_LENGTH 100

int main(int argc, char *argv[]) {
    int nSocket, nClientSocket;
    int nBind, nListen;
    int nFoo = 1;
    std::regex const content_length_pattern = std::regex("Content-Length: ([0-9]+)\r\n");
    std::unordered_map<std::string, std::string> notes;
    notes["some title"] = "some content";
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

        std::string data;

        char buffer[BUFFER_LENGTH];

        int already_read = 0;
        int content_len = -1;
        int position;

        do {
            already_read += read(nClientSocket, buffer, BUFFER_LENGTH);
            data.append(buffer);
            memset(buffer, 0, sizeof(buffer));
            std::smatch regex_match;
            if(content_len < 0 && std::regex_search(data, regex_match, content_length_pattern)) {
                content_len = std::stoi(regex_match.str(1));
            }
            position = data.rfind("\r\n\r\n");
        } while(position < 0 || already_read < (content_len + position + 4));

        std::cout << data << "\n\n";

        std::string msg;

        if (data.rfind("GET", 0) == 0) {
            std::stringstream ss;
            ss << "HTTP/1.1 200 OK\n"
                  "Content-Length: 100\n"
                  "Content-Type: application/json\n"
                  "\n"
                  "{\n"
                  "\"title\": \"some title\"\n"
                  "\t\"content\": \"";
            ss << notes.at("some title") << "\"\n}";
            msg = ss.str();
//               msg = "HTTP/1.1 200 OK\n"
//                  "Content-Length: 100\n"
//                  "Content-Type: application/json\n"
//                  "\n"
//                  "{\n"
//                  "\"title\": \"title\"\n"
//                  "\"content\": ";
//            msg +=
//                  "</body>";
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

        write(nClientSocket, msg.c_str(), msg.size());

        close(nClientSocket);
    }
}

