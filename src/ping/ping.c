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

    if(argc < 3) {
        printf("Usage: %s IP_dest PORT_dest number_of_packet", argv[0]);
        exit(EXIT_FAILURE);
    }

    int n = 10;
    if(argc == 4) n= atoi(argv[3]);

    for(int i = 0; i < n; i++) {
        if(fork() == 0) {
            int sockfd;
            long sec, nsec;
            struct timespec T1, T2;
            struct sockaddr_in dest_addr;
            char time[1024];
            socklen_t len = sizeof(struct sockaddr_in);

            sockfd = socket(AF_INET, SOCK_DGRAM, NO_FLAGS);
            if(sockfd < 0) {
                perror("Error: ");
                exit(EXIT_FAILURE);
            }

            bzero(&dest_addr, sizeof(dest_addr));
            dest_addr.sin_family = PF_INET;
            inet_pton(AF_INET, argv[1], &(dest_addr.sin_addr));
            dest_addr.sin_port = htons(atoi(argv[2]));

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
            sec = T2.tv_sec - T1.tv_sec; 
            nsec = T2.tv_nsec - T1.tv_nsec; 
            printf(
                "Ping from:%s Port:%d Time: sec=%ld nsec=%ld \n", 
                inet_ntoa(dest_addr.sin_addr),  
                ntohs(dest_addr.sin_port),
                sec, 
                nsec
            );
            close(sockfd);
            return 0;
        }
        sleep(1);
    }

}