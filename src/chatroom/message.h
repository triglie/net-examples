#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>
#include <arpa/inet.h>

namespace triglie
{
    class Message 
    {   
        private: 

            struct sockaddr_in * sender; 

            std::string message; 

        public: 

            Message(); 

            Message(std::string message); 

            Message(std::string message, struct sockaddr_in * sender); 

            std::string get_message();

            void set_message(std::string message); 

            struct sockaddr_in * get_sender(); 

            void set_sender(struct sockaddr_in * sender); 
            
    }; 
}

#endif