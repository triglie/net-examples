#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(int argc, char** argv) {
    int socksender, socklistener;
    char sendline[80];
    struct sockaddr_in dest_addr;
    socklen_t len = sizeof(struct sockaddr_in);

    if(argc < 3) {
        printf("Usage: IP_server PORT_server\n");
        return -1;
    }

    socksender = socket(PF_INET, SOCK_DGRAM, 0);
    if(socksender < 0) {
        printf("Error in socket sender opening ... exit!");
        return -1;
    }

    memset(&dest_addr, 0, len);
    dest_addr.sin_family = AF_INET;
    inet_pton(AF_INET, argv[1], &dest_addr.sin_addr);
    dest_addr.sin_port = htons(atoi(argv[2]));

    for(;;) {
        if(fork() == 0) {
            socklistener = socket(PF_INET, SOCK_DGRAM, 0);
            if(socklistener < 0) {
                printf("Error in socket listener opening ... exit!");
                return -1;
            }
        }
    }
}