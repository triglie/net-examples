#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
#include <sys/socket.h>
#include <time.h>

int main (int argc, char * argv[]) {

    int sockfd;
    int n;
    struct sockaddr_in local_addr, remote_addr;
    char buffer[1024];
    socklen_t len = sizeof(struct sockaddr_in);

    if(argc < 2) {
        printf("Usage: %s PORT\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    sockfd = socket(PF_INET, SOCK_DGRAM, 0);

    bzero(&local_addr, sizeof(local_addr));
    local_addr.sin_family = AF_INET;
    local_addr.sin_addr.s_addr = INADDR_ANY;
    local_addr.sin_port = htons(atoi(argv[1]));

    int status = bind(sockfd, (struct sockaddr*) &local_addr, len);

    if(status < 0) {
        printf("Error in socket binding ... exit\n");
        exit(EXIT_FAILURE);
    }

    for(;;) {
        recvfrom(
                sockfd,
                buffer,
                strlen(buffer),
                0,
                (struct sockaddr*) &remote_addr,
                &len
            );
        if(fork() == 0) {
            time_t T;
            for(int i=0; i<7; i++) {
                T = time(NULL);
                char *res = ctime(&T);
                sendto(
                    sockfd,
                    res,
                    sizeof(res) - 1,
                    0,
                    (struct sockaddr*) &remote_addr,
                    len
                );
                sleep(5);
            }
        }
    }
}