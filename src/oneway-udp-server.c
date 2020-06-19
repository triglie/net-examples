/**
 * @triglie
 * One-way UDP receiver 
 * Usage: oneway-udp-server [port]
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>

#define USAGE "Usage: %s <port>\n"

int main (int argc, char* argv[])
{
	// socket file identifier 
	int socketfd; 
	
	// local and remote socket content 
	struct sockaddr_in local_addr, remote_addr;
	socklen_t len = sizeof(struct sockaddr_in);

	// application data buffer
	char buffer[100]; 

	if (argc < 2) {
		printf(USAGE, argv[0]);
		exit(1);  
	}

	if ((socketfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		printf("Cannot instantiate a socket.\n"); 
		exit(1); 
	}

	memset((char *) &local_addr, 0, len);
	local_addr.sin_family = AF_INET; 
	local_addr.sin_port = htons(atoi(argv[1])); 

	if (bind(socketfd, (struct sockaddr *) &local_addr, len) < 0) {
		printf("Cannot bind the socket\n"); 
		exit(1);
	}

	while(1) {
		recvfrom(socketfd, buffer, 99, 0, (struct sockaddr *) &remote_addr, &len); 
		buffer[100] = '\0';
		 
		printf(
			"Packet from IP:%s Port:%d msg:%s \n", 
			inet_ntoa(remote_addr.sin_addr), 
			ntohs(remote_addr.sin_port), 
			buffer
		); 
	}
}
