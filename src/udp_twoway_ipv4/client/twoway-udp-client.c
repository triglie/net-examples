#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <string.h>

int main(int argc, char** args) {
    int sockfd;
    struct sockaddr_in dest_addr;
    int n;
    char sendline[100];
    char recvline[100];

    if(argc < 3) {
        printf("Usage: client IP_dest PORT_dest\n");
        return -1;
    }

    sockfd = socket(PF_INET, SOCK_DGRAM, 0);
    if(sockfd < 0) {
        printf("Error in socket opening ... exit!\n");
        return -1;
    }

    memset(&dest_addr, 0, sizeof(dest_addr));
    dest_addr.sin_family = AF_INET;
    inet_pton(AF_INET, args[1], &(dest_addr.sin_addr));
    dest_addr.sin_port = htons(atoi(args[2]));

    while(fgets(sendline, 100, stdin) != NULL ) {
        sendto(sockfd, sendline, strlen(sendline), 0, (struct sockaddr *) &dest_addr, sizeof(dest_addr));
        n = recvfrom(sockfd, recvline, strlen(recvfrom) - 1, 0, (struct sockaddr *) &dest_addr, sizeof(dest_addr));
        recvline[n] = 0;
        printf("From IP:%s, Port:%d, msg:%s \n", inet_ntoa(dest_addr.sin_addr), ntohs(dest_addr.sin_port), recvline);
    }

}