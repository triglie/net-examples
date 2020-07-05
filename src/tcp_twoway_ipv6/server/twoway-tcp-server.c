#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>

int main(int argc, char** argv) {
    char ipv6[INET6_ADDRSTRLEN];
    int sockfd, newsockfd, n;
    struct sockaddr_in6 local_addr, remote_addr;
    socklen_t len;
    char mesg[1024];

    if(argc < 2) {
        printf("Usage: server listening_PORT\n");
        return 0;
    }

    sockfd = socket(AF_INET6, SOCK_STREAM, 0);
    if(sockfd < 0) {
        printf("Error in socket opening ... exit!");
        return -1;
    }
    memset(&local_addr, 0, sizeof(local_addr));
    local_addr.sin6_family = AF_INET6;
    local_addr.sin6_port = htons(atoi(argv[1]));

    if(bind(sockfd, (struct sockaddr *) &local_addr, sizeof(local_addr)) < 0) {
        printf("Error in binding. Error n. %d\n", errno);
        return -1;
    }

    listen(sockfd, 5);

    for(;;) {
        len = sizeof(remote_addr);
        newsockfd = accept(sockfd, (struct sockaddr *) &remote_addr, &len);

        if(fork() == 0) {
            close(sockfd);
            for(;;) {
                n = recv(newsockfd, mesg, 1023, 0);
                if(n == 0) return 0;
                mesg[n] = 0;
                inet_ntop(PF_INET6, (struct in6_addr*) &remote_addr.sin6_addr, ipv6, INET6_ADDRSTRLEN);
                printf("Pid=%d: received from %s@%d => %s", getpid(), ipv6, ntohs(remote_addr.sin6_port), mesg);
                send(newsockfd, mesg, n, 0);
            }
            return 0;      
        }
        else close(newsockfd);
    }
}