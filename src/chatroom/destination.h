#ifndef DESTINATION_H
#define DESTINATION_H

#include <string>

namespace triglie 
{
    class Destination 
    {
        private: 

            std::string ip_address; 

            bool enabled; 

        public: 

            Destination(std::string); 

            Destination(std::string ip_address, bool enabled); 

            std::string get_ip_address(); 

            bool is_enabled(); 

            void set_enabled(bool enabled); 
    }; 
}

#endif  
