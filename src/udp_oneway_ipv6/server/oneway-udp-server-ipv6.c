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
  struct sockaddr_in6 local, remote;
  char recvline[BUFFER_SIZE];
  char ipv6_presentation[INET6_ADDRSTRLEN];
  socklen_t len = sizeof(struct sockaddr_in6);
  int socketd;

  if (argc != 2)
  { 
    printf("Please enter the following arguments: <Listening port>\n");
    return -1;
  }

  if((socketd=socket(PF_INET6,SOCK_DGRAM,0)) <0)
  { 
    printf("\nUnable to create socket, terminating...");
    return -1;
  }
  memset(&local,0,len);
  local.sin6_family = AF_INET6;
  local.sin6_port=htons(atoi(argv[1]));

  if(bind(socketd, (struct sockaddr *) &local, len)<0)
  { printf("\nBinding error!");
    return -1;
  }
   
  while (1)
  { 
    recvfrom(socketd,recvline,strlen(recvline),0, (struct sockaddr *)&remote, &len);
    inet_ntop(AF_INET6, &remote, ipv6_presentation, sizeof(ipv6_presentation));
    printf("Received from '%s' : '%s'", ipv6_presentation, recvline);
  }
  return 0;
}