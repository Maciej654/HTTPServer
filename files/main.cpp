#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>
#include <map>
#include "Server.h"

#define SERVER_PORT 1234

int main(int argc, char *argv[]) {
    Server server(SERVER_PORT);
    server.runServer();
}
