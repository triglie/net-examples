#include <iostream>
#include <vector>

#include "destination.h"
#include "fileparser.h"
#include "app.h"

int main (int argc, char* argv[]) 
{
    triglie::App appl = triglie::App::get_instance()
        .check_parameters(argc, argv)
        .set_filepath(argv[1]);

    triglie::FileParser fileParser(appl.get_filepath());
    fileParser.parse(); 

    appl.set_destinations_list(fileParser.get_destinations())
        .choose_destinations()
        .start_listener_process()
        .open_chatroom(); 
}