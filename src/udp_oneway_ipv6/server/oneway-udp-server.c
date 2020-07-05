#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <errno.h>

int main(int argc, char** argv) {
    
    char str[INET6_ADDRSTRLEN];
    int sockfd;
    struct sockaddr_in6 local_addr, remote_addr;
    socklen_t len = sizeof(struct sockaddr_in6);
    char buffer[256];

    if(argc < 2) {
        printf("Usage: server6 PORT\n");
        return 1;
    }

    sockfd = socket(PF_INET6, SOCK_DGRAM, 0);
    if(sockfd < 0) {
        printf("Error in socket opening ... exit!");
        return -1;
    }

    memset((char *) &local_addr, 0, len);
    local_addr.sin6_family = AF_INET6;
    local_addr.sin6_port = htons(atoi(argv[1]));

    if(bind(sockfd, (struct sockaddr *) &local_addr, sizeof(local_addr)) < 0) {
        printf("Binding error! Error code n. %d \n", errno);
        return -1;
    }

    for(;;) {
        recvfrom(sockfd, buffer, 99, 0, (struct sockaddr *) &remote_addr, &len);
        inet_ntop(PF_INET6, (struct in6_addr *) &remote_addr.sin6_addr, str, INET6_ADDRSTRLEN);
        printf("Packet from IP:%s, Port:%d, msg:%s \n", str,ntohs(remote_addr.sin6_port), buffer);
    }
}