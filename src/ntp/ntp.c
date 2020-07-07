#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <errno.h>
#include <time.h>

#define TOTAL_PACKETS   6
#define ZERO_FLAGS      0
#define BUFFER_SIZE     1024

int main (int argc, char * argv[]) 
{
    int     socket_fd;
    struct  timeval timeout = {7,0}; 
    struct  sockaddr_in destination, remote; 
    char    *server_ip, 
            *server_port; 
    char    buffer[BUFFER_SIZE]; 
    int     socklen = sizeof(struct sockaddr_in); 
    int     bytes_receiver; 

    if (argc < 3) {
        printf("[error] usage %s <ntp server ip> <port> \n", argv[0]); 
        exit(EXIT_FAILURE); 
    }
    else {
        server_ip   = argv[1]; 
        server_port = argv[2]; 
    }

    socket_fd = socket(AF_INET, SOCK_DGRAM, ZERO_FLAGS); 

    if (socket_fd < 0) {
        perror("[error]"); 
        exit(EXIT_FAILURE); 
    }

    bzero(&destination, sizeof(destination)); 
    destination.sin_family  = AF_INET; 
    inet_pton(AF_INET, server_ip, &(destination.sin_addr)); 
    destination.sin_port    = htons(atoi(server_port)); 

    printf("[ntp] sending request to ntp server \n"); 

    sendto(
        socket_fd, 
        "SIN", 
        strlen("SIN"), 
        ZERO_FLAGS, 
        (struct sockaddr *) &destination, 
        sizeof(destination)
    ); 

    setsockopt(
        socket_fd,
        SOL_SOCKET,
        SO_RCVTIMEO,
        (char*) &timeout,
        sizeof(struct timeval)
    );

    printf("[ntp] waiting for ntp server response. \n\n"); 
    printf("[ntp response] Day Mon Num hh:mm:ss year\n"); 
    printf("----------------------------------------\n"); 

    for (int i = 0; i < TOTAL_PACKETS; ++i) {

        bzero(buffer, BUFFER_SIZE); 

        bytes_receiver = recvfrom(
            socket_fd, 
            buffer, 
            BUFFER_SIZE, 
            ZERO_FLAGS, 
            (struct sockaddr *) &remote, 
            &socklen
        ); 

        if (bytes_receiver < 0) 
            printf("[ntp response] packet timeout. \n"); 
        else {
            buffer[bytes_receiver] = '\0'; 
            printf("[ntp response] %s \n", buffer); 
        }
    }

    return EXIT_SUCCESS; 
}