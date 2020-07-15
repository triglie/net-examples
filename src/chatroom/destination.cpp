#include "destination.h"

triglie::Destination::Destination(std::string ip_address)
{
    this->ip_address = ip_address;
    this->enabled = false; 
}


triglie::Destination::Destination(std::string ip_address, bool enabled)
{
    this->ip_address = ip_address;
    this->enabled = enabled; 
}

std::string triglie::Destination::get_ip_address() 
{
    return this->ip_address; 
}

bool triglie::Destination::is_enabled()
{
    return this->enabled; 
}

void triglie::Destination::set_enabled(bool enabled)
{
    this->enabled = enabled; 
}
