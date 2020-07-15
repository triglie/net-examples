#include "fileparser.h"

triglie::FileParser::FileParser(std::string filepath)
{
    if (this->load_file(filepath) == false) {

        perror("[error]");        
        exit(EXIT_FAILURE); 
    }
}

bool triglie::FileParser::load_file(std::string filepath)
{
    source_file.open(filepath); 
    return source_file.good(); 
}

void triglie::FileParser::parse()
{
    std::string ip; 
    while (getline(source_file, ip)) 
        destination_vector.push_back(new Destination(ip));
}

std::vector<triglie::Destination *> triglie::FileParser::get_destinations()
{
    return this->destination_vector; 
}