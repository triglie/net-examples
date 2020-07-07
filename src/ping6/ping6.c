#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <errno.h>

#define NO_FLAGS 0

int main(int argc, char** argv) {

    int packets = 10;

    if(argc < 3) {
        printf("[error] usage: %s <ip> <port> [#packets]", argv[0]);
        exit(EXIT_FAILURE);
    }

    if(argc == 4) 
        packets = atoi(argv[3]);

    for(int i = 0; i < packets; i++) {
        if(fork() == 0) {

            int       sockfd;
            long      sec, nsec, ms;
            struct    timespec T1, T2;
            struct    sockaddr_in6 dest_addr;
            char      time[1024];
            socklen_t len = sizeof(struct sockaddr_in6);

            sockfd = socket(AF_INET6, SOCK_DGRAM, NO_FLAGS);
            if(sockfd < 0) {
                perror("Error: ");
                exit(EXIT_FAILURE);
            }

            bzero(&dest_addr, sizeof(dest_addr));
            dest_addr.sin6_family = PF_INET6;
            inet_pton(AF_INET6, argv[1], &(dest_addr.sin6_addr));
            dest_addr.sin6_port = htons(atoi(argv[2]));

            clock_gettime(CLOCK_REALTIME, &T1);

            sendto(
                sockfd, 
                "ACK", 
                strlen("ACK"), 
                NO_FLAGS, 
                (struct sockaddr*) &dest_addr, 
                sizeof(struct sockaddr_in)
            );

            recvfrom(
                sockfd,
                time,
                strlen(time),
                NO_FLAGS,
                (struct sockaddr*) &dest_addr,
                &len
            );
            
            clock_gettime(CLOCK_REALTIME, &T2);

            sec  = T2.tv_sec - T1.tv_sec; 
            nsec = T2.tv_nsec - T1.tv_nsec; 
            ms = sec > 0 ? sec * 1000 : nsec / 1000000; 

            printf("Ping from:%s Port:%d Time: ms=%ld \n", argv[1], argv[2], ms);

            close(sockfd);
            return 0;
        }
        sleep(1);
    }

}