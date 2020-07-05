#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

int main(int argc, char** argv) {

    int sockfd;
    struct sockaddr_in6 dest_addr;
    extern int errno;
    char buffer[100];
    int n;

    if(argc < 3) {
        printf("Usage: client6 IPv6_Dest Port_Dest\n");
        return -1;
    }

    sockfd = socket(PF_INET6, SOCK_DGRAM, 0);

    if(sockfd < 0) {
        printf("Error in socket opening ... exit!\n");
        return -1;
    }

    memset(&dest_addr, 0, sizeof(dest_addr));
    dest_addr.sin6_family = AF_INET6;
    inet_pton(AF_INET6, argv[1], &(dest_addr.sin6_addr));
    dest_addr.sin6_port = htons(atoi(argv[2]));

    printf("Insert an integer:\n");
    scanf("%d", &n);

    for(int i=0; i<10; i++) {
        sprintf(buffer, "%d", i+n);
        printf("sending %s\n", buffer);
        sendto(sockfd, buffer, strlen(buffer)+1, 0, (struct sockaddr*) &dest_addr, sizeof(dest_addr));
    }
}