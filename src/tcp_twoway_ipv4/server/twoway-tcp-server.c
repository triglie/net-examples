#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <errno.h>

#define TRUE 1

int main(int argc, char** argv) {
    int sockfd, newsockfd, n;
    struct sockaddr_in local_addr, remote_addr;
    socklen_t len;
    char mesg[1024];

    if(argc < 2) {
        printf("Usage: server listening_PORT\n");
        return 0;
    }

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0) {
        printf("Error in socket opening ... exit!");
        return -1;
    }
    memset(&local_addr, 0, sizeof(local_addr));
    local_addr.sin_family = AF_INET;
    local_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    local_addr.sin_port = htons(atoi(argv[1]));

    if(bind(sockfd, (struct sockaddr *) &local_addr, sizeof(local_addr)) < 0) {
        printf("Error in binding. Error n. %d\n", errno);
        return -1;
    }

    listen(sockfd, 5);

    while (TRUE) {
        len = sizeof(remote_addr);
        newsockfd = accept(sockfd, (struct sockaddr *) &remote_addr, &len);
        
        sprintf(mesg, "init"); 
        if(fork() == 0) {
            close(sockfd);
            while (strcmp(mesg, "quit") != 0) {
                n = recv(newsockfd, mesg, 1023, 0);
                if(n == 0) return 0;
                mesg[n] = 0;
                printf("Pid=%d: received from %s@%d => %s \n", getpid(), inet_ntoa(remote_addr.sin_addr), ntohs(remote_addr.sin_port), mesg);
                send(newsockfd, mesg, n, 0);
            }
            return 0;      
        }
        else close(newsockfd); 
    }

    return 0; 
}