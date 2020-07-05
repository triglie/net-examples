#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <string.h>

int main(int argc, char** args) {
    char ipv6[INET6_ADDRSTRLEN];
    int sockfd;
    struct sockaddr_in6 dest_addr;
    int n;
    char sendline[100];
    char recvline[100];
    socklen_t len = sizeof(struct sockaddr_in6);

    if(argc < 3) {
        printf("Usage: client IP_dest PORT_dest\n");
        return -1;
    }

    sockfd = socket(PF_INET6, SOCK_DGRAM, 0);
    if(sockfd < 0) {
        printf("Error in socket opening ... exit!\n");
        return -1;
    }

    memset(&dest_addr, 0, len);
    dest_addr.sin6_family = AF_INET6;
    inet_pton(AF_INET6, args[1], &(dest_addr.sin6_addr));
    dest_addr.sin6_port = htons(atoi(args[2]));

    while(fgets(sendline, 100, stdin) != NULL ) {
        sendto(sockfd, sendline, strlen(sendline), 0, (struct sockaddr *) &dest_addr, len);
        n = recvfrom(sockfd, recvline, 99, 0, (struct sockaddr *) &dest_addr, &len);
        recvline[n] = 0;
        inet_ntop(PF_INET6, (struct in6_addr*) &dest_addr.sin6_addr, ipv6, INET6_ADDRSTRLEN);
        printf("[%s@%d => client] %s \n", ipv6, ntohs(dest_addr.sin6_port), recvline);
    }

}