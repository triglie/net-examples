#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <errno.h>

#define BUFFERSIZE  1024 
#define NOFLAGS     0
#define TRUE        1

int main (int argc, char * argv[]) 
{
    /** socket file descriptor */
    int sockfd; 

    /** locale and remote structs */
    struct sockaddr_in locale, remote; 

    char rcv_buffer[BUFFERSIZE]; 
    char snd_buffer[BUFFERSIZE]; 

    int command_status, 
        bytes_received; 

    char * server_ip, 
         * server_port; 

    if (argc < 3) {
        printf("[usage] %s <remote ip> <remote port> \n", argv[0]);
        exit(-1); 
    }
    else {
        server_ip = argv[1]; 
        server_port = argv[2]; 
    }

    sockfd = socket(AF_INET, SOCK_STREAM, NOFLAGS);

    if (sockfd < 0) {
        perror("[error] "); 
        exit(-1); 
    } 

    memset(&remote, 0, sizeof(remote)); 
    remote.sin_family = AF_INET; 
    remote.sin_addr.s_addr = inet_addr(server_ip);
    remote.sin_port = htons(atoi(server_port));  

    command_status = connect(sockfd, (struct sockaddr *) &remote, sizeof (remote)); 

    memset(rcv_buffer, 0, sizeof(rcv_buffer)); 
    memset(snd_buffer, 0, sizeof(snd_buffer)); 

    if (command_status < 0) {
        perror("[error] "); 
        exit(-1); 
    } 

    while (TRUE) {

        /** read from stdin */
        scanf("%s", snd_buffer); 
        snd_buffer[BUFFERSIZE - 1] = '\0'; 

        /** send message and wait for response */
        send(sockfd, snd_buffer, strlen(snd_buffer), NOFLAGS); 
        bytes_received = recv(sockfd, rcv_buffer, BUFFERSIZE - 1, NOFLAGS);

        /** sanitize receiving buffer */
        rcv_buffer[bytes_received] = '\0'; 

        /** print to stdout */
        printf(
            "[%s@%d => local] %s \n",
            inet_ntoa(remote.sin_addr), 
            ntohs(remote.sin_port), 
            rcv_buffer 
        ); 
    }
}