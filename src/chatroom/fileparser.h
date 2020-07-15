#ifndef FILE_PARSER_H
#define FILE_PARSER_H

#include <string>
#include <vector>
#include <fstream>
#include <errno.h>

#include "destination.h"

/** just for debugging */
// #include <iostream>

namespace triglie 
{
    class FileParser 
    {
        private: 

            std::fstream source_file; 

            std::vector<Destination*> destination_vector; 

        protected: 

            bool load_file(std::string filepath); 

        public: 
        
            FileParser(std::string filepath); 

            void parse(); 

            std::vector<triglie::Destination*> get_destinations(); 

    }; 
}

#endif  