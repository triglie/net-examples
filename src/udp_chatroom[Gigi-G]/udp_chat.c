#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char** argv) {
    int socksender, socklistener;
    char sendbuffer[80];
    char receivebuffer[80];
    char receivelistener[80];
    struct sockaddr_in local_addr, dest_addr, remote_addr;
    socklen_t len = sizeof(struct sockaddr_in);
    int n;

    if(argc < 2) {
        printf("Usage: PORT\n");
        return -1;
    }

    if(fork() == 0) {
        close(socksender);
        socklistener = socket(PF_INET, SOCK_DGRAM, 0);
        if(socklistener < 0) {
            printf("Error in socket listener opening ... exit!");
            return -1;
        }

        memset(&local_addr, 0, len);
        local_addr.sin_family = AF_INET;
        local_addr.sin_addr.s_addr = htonl(INADDR_ANY);
        local_addr.sin_port = htons(atoi(argv[1]));

        int status = bind(socklistener, (struct sockaddr *) &local_addr, len);
        if(status < 0) {
            printf("Cannot bind the socket\n");
            exit(1);
        }
        while(1) {
            n = recvfrom(socklistener, receivelistener, 79, 0, (struct sockaddr *) &remote_addr, &len); 
            receivelistener[n] = 0;
            printf(
                "Packet from IP:%s Port:%d msg:%s\n", 
                inet_ntoa(remote_addr.sin_addr), 
                ntohs(remote_addr.sin_port), 
                receivelistener
            );

            sendto(socklistener, "ACK", strlen("ACK"), 0, (struct sockaddr*) &remote_addr, len);
        }
        return 0;
    }
    else {
        int c;
        char count = '0';
        FILE *file;
        file = fopen("client.txt", "r");
        if(file) {
            while ((c = getc(file)) != EOF) {
                if(c == '\n') {
                    putchar('[');
                    putchar(count);
                    putchar(']');
                    putchar(c);
                    count++;
                }else {
                    putchar(c);
                }
            }
            fclose(file);
        }
        int client[count];
        for(int i=0; i<count; i++) {
            client[i] = 0;
        }
        printf("Type enter to start chatting:\n");
        while(1) {
            fgets(sendbuffer,80,stdin);
            printf("Write a message for clients\n");
            fgets(sendbuffer,80,stdin);
            n = 0;
            char input[2] = {0};
            printf("Select clients and write quit:\n");
            while(strcmp("q", input)) {
                fgets(input, 2, stdin);
                input[1] = '\0';
                n = input[0] - 48;
                if(n >= 0 && n < count) {
                    client[n] = 1;
                }
            }
            file = fopen("client.txt", "r");
            char receiver[33];
            count = 0;
            int i = 0;
            int find = 0;
            if(file) {
                while ((c = getc(file)) != EOF) {
                    if(c == '\n') {
                        count++;
                        if(find){
                            receiver[i] = 0;
                            char *res = receiver;
                            if(fork() == 0) {
                                socksender = socket(PF_INET, SOCK_DGRAM, 0);
                                if(socksender < 0) {
                                    printf("Error in socket sender opening ... exit!");
                                    return -1;
                                }
                                memset(&dest_addr, 0, len);
                                dest_addr.sin_family = AF_INET;
                                inet_pton(AF_INET, res, &dest_addr.sin_addr);
                                dest_addr.sin_port = htons(atoi(argv[1]));
                                sendto(socksender, sendbuffer, strlen(sendbuffer), 0, (struct sockaddr*) &dest_addr, len);
                                n = recvfrom(socksender, receivebuffer, 79, 0, (struct sockaddr *) &dest_addr, &len);
                                receivebuffer[n] = 0;
                                printf("[%s:%d => client] %s \n", inet_ntoa(dest_addr.sin_addr), ntohs(dest_addr.sin_port), receivebuffer);
                                close(socksender);
                                exit(0);
                            }
                            else {
                                for(int j=0; j<count; j++) {
                                    client[j] = 0;
                                }
                                for(int j = 0; j<32; j++) {
                                    receiver[j] = 0;
                                }
                                i = 0;
                                find = 0;
                            }
                        }
                    }
                    else if(client[count]) {
                        receiver[i++] = c;
                        find = 1;
                    }
                }
                fclose(file);
            }
        }
        return 0;
    }
}