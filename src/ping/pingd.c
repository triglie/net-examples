#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <arpa/inet.h>
#include <errno.h>

#define NO_FLAGS    0
#define TRUE        1
#define BUFFER_SIZE 1024

int main (int argc, char * argv[])
{
    int     sockfd; 
    struct  sockaddr_in local, remote; 
    char *  listening_port; 
    int     command_status; 
    int     bytes_read; 
    char    buffer[BUFFER_SIZE]; 
    int     socklen  = sizeof(struct sockaddr_in); 
    int     _socklen = sizeof(struct sockaddr_in); 

    if (argc < 2) {
        printf("[error] usage: %s <listening port> \n", argv[0]); 
        exit(EXIT_FAILURE); 
    } 
    else listening_port = argv[1]; 

    sockfd = socket(AF_INET, SOCK_DGRAM, NO_FLAGS); 

    if (sockfd < 0) {
        perror("[error]"); 
        exit(EXIT_FAILURE); 
    }

    bzero(&remote, sizeof(remote));  
    bzero(&local, sizeof(local));
    local.sin_family = AF_INET; 
    local.sin_port = htons(atoi(listening_port)); 

    command_status = bind(sockfd, (struct sockaddr *) &local, socklen); 

    if (command_status < 0) {
        perror("[error]"); 
        exit(EXIT_FAILURE); 
    }

    printf("[status] pingd server started at port %s \n", listening_port); 

    while (TRUE) {

        bytes_read = recvfrom(
            sockfd, 
            buffer, 
            BUFFER_SIZE, 
            NO_FLAGS, 
            (struct sockaddr *) &remote, 
            &_socklen
        ); 

        buffer[bytes_read] = '\0'; 

        sendto(
            sockfd, 
            buffer, 
            bytes_read, 
            NO_FLAGS, 
            (struct sockaddr *) &remote, 
            socklen
        ); 
    }
}