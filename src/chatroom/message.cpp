#include "message.h"

triglie::Message::Message() 
{
    // nothing 
}

triglie::Message::Message(std::string message)
{
    this->message = message; 
}

triglie::Message::Message(std::string message, struct sockaddr_in * sender)
{
    this->message = message; 
    this->sender = sender; 
}

std::string triglie::Message::get_message()
{
    return message; 
}

void triglie::Message::set_message(std::string message)
{
    this->message = message; 
}

struct sockaddr_in * triglie::Message::get_sender()
{
    return sender; 
}

void triglie::Message::set_sender(struct sockaddr_in * sender)
{
    this->sender = sender; 
}