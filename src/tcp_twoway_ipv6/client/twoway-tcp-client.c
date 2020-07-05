#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/types.h>
#include <netdb.h>

#define BUFFERSIZE  1024 
#define NOFLAGS     0
#define TRUE        1

int main (int argc, char * argv[]) 
{
    /** socket file descriptor */
    int sockfd; 

    /** locale and remote structs */
    struct sockaddr_in6 remote;  

    char    rcv_buffer[BUFFERSIZE], 
            snd_buffer[BUFFERSIZE],
            ipv6_remote[INET6_ADDRSTRLEN]; 

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

    sockfd = socket(AF_INET6, SOCK_STREAM, NOFLAGS);

    if (sockfd < 0) {
        perror("[error] "); 
        exit(-1); 
    } 

    memset(&remote, 0, sizeof(struct sockaddr_in6)); 
    remote.sin6_family = AF_INET6; 
    inet_pton(AF_INET6, server_ip, &(remote.sin6_addr));
    remote.sin6_port = htons(atoi(server_port));  

    command_status = connect(sockfd, (struct sockaddr *) &remote, sizeof(remote)); 

    if (command_status < 0) {
        perror("[error] "); 
        exit(-1); 
    } 

    memset(rcv_buffer, 0, sizeof(rcv_buffer)); 
    memset(snd_buffer, 0, sizeof(snd_buffer)); 

    while (TRUE) {

        /** read from stdin */
        scanf("%s", snd_buffer); 
        snd_buffer[BUFFERSIZE - 1] = '\0'; 

        /** send message and wait for response */
        send(sockfd, snd_buffer, strlen(snd_buffer), NOFLAGS); 
        bytes_received = recv(sockfd, rcv_buffer, BUFFERSIZE - 1, NOFLAGS);

        /** sanitize receiving buffer */
        rcv_buffer[bytes_received] = '\0'; 

        /** retrieve server ipv6 */
        inet_ntop(AF_INET6, (struct in6_addr*) &remote.sin6_addr, ipv6_remote, INET6_ADDRSTRLEN);

        /** print to stdout */
        printf(
            "[%s@%d => local] %s \n",
            ipv6_remote, 
            ntohs(remote.sin6_port), 
            rcv_buffer 
        ); 
    }
}