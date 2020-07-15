#include "chatsocket.h"

void triglie::ChatSocket::handle_io_status(int status)
{
    if (status > 0) return; 
    perror("[system error]"); 
    exit(EXIT_FAILURE); 
}

triglie::ChatSocket::ChatSocket()
{
    this->handle_io_status(
        socket_file_descriptor = socket(
            AF_INET, 
            SOCK_DGRAM,
            ZERO_FLAGS  
        )
    ); 
} 