/**
 * Socket step: 
 * 
 * step condivisi
 * - open socket  
 * - send 
 * - receive 
 * 
 * listener: 
 * - bind 
 * 
 * sender: 
 * 
 * 
 */ 

#ifndef CHAT_SOCKET_H 
#define CHAT_SOCKET_H

#include <arpa/inet.h>
#include <iostream>
#include <errno.h>

#include "message.h"

#define ZERO_FLAGS  0
#define CHAT_CPORT  8700

namespace triglie
{
    class ChatSocket 
    {
        
        private: 

            int socket_file_descriptor; 

        protected: 

            void handle_io_status(int status); 

        public: 

            ChatSocket(); 

            virtual void send (Message * message) = 0; 

            virtual Message * receive () = 0; 
    }; 
}

#endif