/*
@Le triglie fritte
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#define BUFFER_SIZE 1000

int main(int argc, char**argv)
{ 
  struct sockaddr_in6 addr;
  char sendline[BUFFER_SIZE];
  socklen_t len = sizeof(struct sockaddr_in6);
  int socketd;

  if (argc != 3)
  { 
    printf("Please enter the following arguments: <Target's IPv6> <Target's port>\n");
    return -1;
  }

  if((socketd=socket(PF_INET6,SOCK_DGRAM,0)) <0)
  { 
    printf("\nUnable to create socket, terminating...");
    return -1;
  }
  memset(&addr,0,len);
  addr.sin6_family = AF_INET6;
  inet_pton(AF_INET6, argv[1], &(addr.sin6_addr)); 
  addr.sin6_port=htons(atoi(argv[2]));
   
  while (fgets(sendline, BUFFER_SIZE,stdin) != NULL)
  { 
    printf("Sending '%s' to '%s'", sendline, argv[1]);
    sendto(socketd,sendline,strlen(sendline),0, (struct sockaddr *)&addr, len);
  }
  return 0;
}