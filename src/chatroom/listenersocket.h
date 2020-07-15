#ifndef LISTENER_SOCKET_H 
#define LISTENER_SOCKET_H 

#include "chatsocket.h"
#include "message.h"

namespace triglie
{
    class ListenerSocket : public ChatSocket
    {
        protected:; 

        public: 

            ListenerSocket(); 

            void send (Message * message); 

            Message * receive (); 
    }; 
}

#endif