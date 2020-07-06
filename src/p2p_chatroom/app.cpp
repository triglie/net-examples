#include <iostream>
#include <fstream>
#include <vector> 
#include <arpa/inet.h> 
#include <stdlib.h> 
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define HOSTFILE            "hosts"
#define LISTENER_PORT       9898
#define MAX_MESSAGE_LENGTH  1024
#define ZERO_FLAGS          0 

class Destination 
{
    public: 
        std::string ip;
        bool sendto; 

    Destination (std::string ip, bool sendto = false) {
        this->ip = ip; 
        this->sendto = sendto; 
    }

    void enable () {
        this->sendto = true; 
    }

    void disable() {
        this->sendto = false; 
    }
}; 

class Message 
{
    public: 

        std::string sender_ip;
        int sender_port;  
        std::string message;
        struct sockaddr_in sender; 

        Message(struct sockaddr_in * sender, char message[]) {
            memcpy(&this->sender, sender, sizeof(struct sockaddr_in)); 
            sender_ip = inet_ntoa(sender->sin_addr), 
            sender_port = htons(sender->sin_port), 
            this->message = message; 
        } 
}; 

int main (int argc, char * argv[])
{
    /*--------------------------------------------------------- /
     * Vengono caricati in memoria i destinatari, leggendone gli
     * indirizzi dal file hosts. 
     *---------------------------------------------------------*/
    
    std::vector<Destination*> hosts; 
    std::fstream hostsfile; 
    hostsfile.open(HOSTFILE, std::fstream::in); 

    if (!hostsfile.good()) 
        std::cout << "Errore nella lettura del file hosts. \n"; 
    
    std::string ip_address; 

    while (getline(hostsfile, ip_address)) 
        hosts.push_back(new Destination(ip_address)); 

    /*--------------------------------------------------------- /
     * Creiamo un processo figlio che possa ricevere i messaggi
     * allo stesso tempo. 
     *---------------------------------------------------------*/

    if (fork() == 0) {

        ListenerSocket lsocket; 
        while (true) {

            Message *msg = lsocket.receive(); 
            lsocket.sendAck(msg); 

            printf(
                "[%s:%d] %s \n>> ",
                msg->sender_ip.c_str(), 
                msg->sender_port, 
                msg->message.c_str()
            ); 

        }
        return 0; 
    }

    /*--------------------------------------------------------- /
     * L'utente deve selezionare i destinatari a cui inviare il
     * i messaggi in broadcast. 
     *---------------------------------------------------------*/

    int user_input = 0; 

    while (user_input >= 0) {

        int i = 0; 
        system("clear"); 

        std::cout << "Host disponibili: \n"; 
        for (Destination * dest : hosts) 
            std::cout << i++ << ") " << dest->ip << std::endl; 

        std::cout << "Seleziona l'host tramite l'identificativo. \n"; 
        std::cout << "inserisci un numero negativo per fermarti. \n";  
        
        std::cin >> user_input; 

        if (user_input >= 0)
            // activate destination 
            hosts[user_input]->enable();  
    }

    /*--------------------------------------------------------- /
     * I destinatari sono stati selezionati. Adesso l'utente
     * può inviare i messaggi in broadcast. 
     *---------------------------------------------------------*/

    std::string message; 

    system("clear"); 
    std::cout << "[Chatroom] \n"; 
    std::cout << "lista broadcast: \n"; 
    for (Destination * dest : hosts) 
        if (dest->sendto) 
            std::cout << dest->ip << std::endl;
    
    std::cout << "\n\n>> "; 
    std::cin >> message; 
    
    wait(NULL); 
    return 0; 
}