// #include <iostream>
// #include <fstream>
// #include <vector> 
// #include <arpa/inet.h> 
// #include <stdlib.h> 
// #include <unistd.h>
// #include <string.h>
// #include <sys/types.h>
// #include <sys/wait.h>
// #include <sys/time.h>

// #define HOSTFILE            "hosts"
// #define LISTENER_PORT       9898
// #define MAX_MESSAGE_LENGTH  1024
// #define ZERO_FLAGS          0 

// class Destination 
// {
//     public: 
//         std::string ip;
//         bool sendto; 

//     Destination (std::string ip, bool sendto = false) {
//         this->ip = ip; 
//         this->sendto = sendto; 
//     }

//     void enable () {
//         this->sendto = true; 
//     }

//     void disable() {
//         this->sendto = false; 
//     }
// }; 

// class Message 
// {
//     public: 

//         std::string sender_ip;
//         int sender_port;  
//         std::string message;
//         struct sockaddr_in sender; 

//         Message(struct sockaddr_in * sender, char message[]) {
//             memcpy(&this->sender, sender, sizeof(struct sockaddr_in)); 
//             sender_ip = inet_ntoa(sender->sin_addr), 
//             sender_port = htons(sender->sin_port), 
//             this->message = message; 
//         } 
// }; 

// class ListenerSocket 
// {
//     private: 
//         int file_descriptor; 
//         struct sockaddr_in listener; 
//         struct sockaddr_in sender; 

//         void _check_status (int status) {
//             if (status >= 0) return; 
//             perror("[error]");
//             exit(-1); 
//         }
        
//         int _bind() {
//             bzero((char *) &(listener), sizeof(listener)); 
//             listener.sin_family = AF_INET; 
//             listener.sin_port = htons(LISTENER_PORT); 
//             return bind(
//                 file_descriptor, 
//                 (struct sockaddr *) &listener,
//                 sizeof(listener)
//             ); 
//         }

//     public:

//         ListenerSocket () { 
//             this->_check_status(file_descriptor = socket(AF_INET, SOCK_DGRAM, ZERO_FLAGS)); 
//             this->_check_status(this->_bind()); 
//         }

//         Message* receive () {

//             int msg_length = 0; 
//             char message[MAX_MESSAGE_LENGTH]; 
//             socklen_t sender_length = sizeof(sender); 

//             msg_length = recvfrom(
//                 file_descriptor, 
//                 message, 
//                 MAX_MESSAGE_LENGTH, 
//                 ZERO_FLAGS, 
//                 (struct sockaddr *) &sender, 
//                 &sender_length
//             ); 

//             message[msg_length] = '\0'; 

//             return new Message(&sender, message); 
//         }

//         void sendAck(Message* msg) {
//             socklen_t socklen = sizeof(struct sockaddr_in); 

//             sendto(
//                 file_descriptor, 
//                 msg->message.c_str(),
//                 sizeof( msg->message.c_str() ), 
//                 ZERO_FLAGS, 
//                 (struct sockaddr *) &(msg->sender), 
//                 socklen
//             ); 
//         }

// }; 

// int main (int argc, char * argv[])
// {
//     /*--------------------------------------------------------- /
//      * Vengono caricati in memoria i destinatari, leggendone gli
//      * indirizzi dal file hosts. 
//      *---------------------------------------------------------*/
    
//     std::vector<Destination*> hosts; 
//     std::fstream hostsfile; 
//     hostsfile.open(HOSTFILE, std::fstream::in); 

//     if (!hostsfile.good()) 
//         std::cout << "Errore nella lettura del file hosts. \n"; 
    
//     std::string ip_address; 

//     while (getline(hostsfile, ip_address)) 
//         hosts.push_back(new Destination(ip_address)); 

//     /*--------------------------------------------------------- /
//      * Creiamo un processo figlio che possa ricevere i messaggi
//      * allo stesso tempo. 
//      *---------------------------------------------------------*/

//     if (fork() == 0) {

//         ListenerSocket lsocket; 
//         while (true) {

//             Message *msg = lsocket.receive(); 
//             lsocket.sendAck(msg); 

//             printf(
//                 "[%s:%d] %s \n>> ",
//                 msg->sender_ip.c_str(), 
//                 msg->sender_port, 
//                 msg->message.c_str()
//             ); 

//         }
//         return 0; 
//     }

//     /*--------------------------------------------------------- /
//      * L'utente deve selezionare i destinatari a cui inviare il
//      * i messaggi in broadcast. 
//      *---------------------------------------------------------*/

//     int user_input = 0; 

//     while (user_input >= 0) {

//         int i = 0; 
//         system("clear"); 

//         std::cout << "Host disponibili: \n"; 
//         for (Destination * dest : hosts) 
//             std::cout << i++ << ") " << dest->ip << std::endl; 

//         std::cout << "Seleziona l'host tramite l'identificativo. \n"; 
//         std::cout << "inserisci un numero negativo per fermarti. \n";  
        
//         std::cin >> user_input; 

//         if (user_input >= 0)
//             // activate destination 
//             hosts[user_input]->enable();  
//     }

//     /*--------------------------------------------------------- /
//      * I destinatari sono stati selezionati. Adesso l'utente
//      * può inviare i messaggi in broadcast. 
//      *---------------------------------------------------------*/

//     std::string message; 

//     system("clear"); 
//     std::cout << "[Chatroom] \n"; 
//     std::cout << "lista broadcast: \n"; 
//     for (Destination * dest : hosts) 
//         if (dest->sendto) 
//             std::cout << dest->ip << std::endl;
    
//     /*--------------------------------------------------------- /
//      * Apriamo una socket per l'invio dei messaggi ai destinatari 
//      *---------------------------------------------------------*/
    
//     int sendersocket = socket(AF_INET, SOCK_DGRAM, ZERO_FLAGS); 
//     struct sockaddr_in destination_addr;

//     if (sendersocket < 0) {
//         perror("[error]"); 
//         exit(-1); 
//     }

//     // imposto il timeout a 2 secondi per l'ack del messaggio. 
//     struct timeval timeout={2,0}; 
//     setsockopt(
//         sendersocket,
//         SOL_SOCKET,
//         SO_RCVTIMEO,
//         (char*)&timeout,
//         sizeof(struct timeval)
//     );

//     bzero(&destination_addr, sizeof(struct sockaddr_in));
//     destination_addr.sin_family = AF_INET;
//     destination_addr.sin_port = htons(LISTENER_PORT);

//     while (true) {
//         char ack[MAX_MESSAGE_LENGTH];
//         socklen_t len = sizeof(struct sockaddr_in);
//         std::cout << ">> "; 
//         std::cin >> message; 

//         for (Destination * dest : hosts) {
//             if (dest->sendto) {
//                 inet_pton(AF_INET, dest->ip.c_str(), &(destination_addr.sin_addr));

//                 sendto(
//                     sendersocket, 
//                     message.c_str(), 
//                     strlen(message.c_str()), 
//                     ZERO_FLAGS, 
//                     (struct sockaddr *) &destination_addr, 
//                     sizeof(struct sockaddr_in)
//                 );

//                 int acklen = recvfrom(
//                     sendersocket, 
//                     ack, 
//                     MAX_MESSAGE_LENGTH - 1, 
//                     ZERO_FLAGS, 
//                     (struct sockaddr *) &destination_addr, 
//                     &len
//                 );

//                 if (acklen < 0) {
//                     printf("errore nell'inoltro a %s \n", dest->ip.c_str()); 
//                 }
//             }            
//         }
//     }
    
//     wait(NULL); 
//     return 0; 
// }