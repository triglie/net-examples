#include "app.h"

triglie::App triglie::App::check_parameters(int argc, char * argv[])
{
    if (argc > 1) return *this; 
    std::cout << "[error] usage: " << (std::string) argv[0] << " <hosts file> \n"; 
    exit(EXIT_FAILURE); 
}

void triglie::App::print_destinations()
{
    int i = 0; 
    for (Destination * dest : destinations) 
        std::cout << i++ << ") " << dest->get_ip_address() << std::endl; 
} 

void triglie::App::print_selection_message() 
{
    std::cout << "Seleziona l'host tramite l'identificativo. \n"; 
    std::cout << "inserisci un numero negativo per fermarti. \n";  
}

std::string triglie::App::get_filepath()
{
    return filepath; 
} 

triglie::App triglie::App::set_filepath(std::string filepath)
{
    this->filepath = filepath; 
    return *this; 
} 

triglie::App triglie::App::set_destinations_list(std::vector<triglie::Destination *> destinations)
{
    this->destinations = destinations; 
    return *this; 
}

triglie::App triglie::App::choose_destinations()
{
    int user_input  = 1; 

    while (user_input >= 0) {
        system("clear");
        print_destinations(); 
        print_selection_message(); 
        std::cin >> user_input; 

        if (user_input >= 0 && user_input < destinations.size())
            destinations[user_input]->set_enabled(true); 
    }
    
    return *this; 
} 

triglie::App triglie::App::start_listener_process() 
{
    return *this;
}

triglie::App triglie::App::open_chatroom()
{
    system("clear"); 
    for (triglie::Destination * dest : destinations) {
        if (dest->is_enabled()) 
            std::cout << dest->get_ip_address() << " \n"; 
    }
    return *this;
}