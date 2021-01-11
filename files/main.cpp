#include "Server.h"

int main(int argc, char *argv[]) {
    if(argc > 2){
        printf("Too many arguments supplied. Exiting.");
        return -1;
    }else if (argc == 2) {
        char *ptr;
        int port;
        port = (int) strtol(argv[1], &ptr, 10);
        if(port > 65353 || port < 0) {
            printf("Wrong port has been chosen. Exiting.");
            return -1;
        }
        Server server(port);
        server.runServer();
    } else {
        Server server (80);
        server.runServer();
    }
}

