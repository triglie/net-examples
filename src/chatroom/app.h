#ifndef APP_H
#define APP_H

#include <iostream>
#include <vector>

#include "destination.h"

namespace triglie
{
    class App 
    {
        private: 

            /**
             *  Destinations host file 
             */
            std::string filepath; 

            /**
             *  Destinations vector  
             */
            std::vector<triglie::Destination *> destinations; 

            App() {}

        protected: 

            void print_destinations(); 
            
            void print_selection_message(); 

        public: 

            /**
             * Get the singleton instance 
             * 
             * @return triglie::App 
             */ 
            static triglie::App& get_instance()
            {
                static App instance; 

                return instance; 
            }

            /**
             * getters and setters
             *  
             */ 
            std::string get_filepath(); 

            triglie::App set_filepath(std::string filepath); 

            triglie::App set_destinations_list(std::vector<triglie::Destination *> destinations); 
            
            /**
             * class methods 
             * 
             */ 

            triglie::App check_parameters(int argc, char * argv[]); 

            triglie::App choose_destinations(); 

            triglie::App start_listener_process(); 

            triglie::App open_chatroom(); 
    };
}

#endif