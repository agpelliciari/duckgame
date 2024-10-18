#include "client/client.h"

#include <cstring>
#include <iostream>
#include <string>

#include "common/liberror.h"

#define ASK_NAME "What is your name?"
#define ACTION_EXIT "Exit"
#define ACTION_PICKUP "Pickup"
#define ACTION_READ "Read"

unsigned int Client::inputnum() {
    unsigned int res;
    if (!(std::cin >> res)) {
        throw LibError(1, "Could not read number argument");
    }

    return res;
}

void Client::listenActions() {
    // Un buffer lo suficientemente grande. Que esta en el stack.

    std::cout << ASK_NAME << std::endl;

    std::string name;
    if (!(std::getline(std::cin, name, '\n'))) {  // Could not read name.
        throw LibError(1, "Could not read player name");
    }
    
    std::string name2;

    std::cerr << ASK_NAME << " segundo player" << std::endl;
    if (!(std::getline(std::cin, name2, '\n'))) {  // Could not read name.
        throw LibError(1, "Could not read second player name");
    }
    if(name2.size() == 0){
       std::cerr << "1 player: "<< name << std::endl;
       protocol.createLobby(1);
    } else{
       std::cerr << "2 players: "<< name << " " << name2 << std::endl;
       protocol.createLobby(2);
    }
    
    

    std::string action;

    while (std::cin >> action) {
        if (action.compare(ACTION_EXIT) == 0) {
            return;
        }
        if (action.compare(ACTION_PICKUP) == 0) {
            uint8_t indplayer = inputnum();  // Se valida en el server.
            uint8_t box = inputnum();  // Se valida en el server.
            
            if(indplayer == 1){
                std::cerr << "Picked up " << name2 <<" box: "<< (int)box << std::endl;
                protocol.pickup(name2,1, box);
            } else{
                std::cerr << "Picked up " << name <<" box: "<< (int)box << std::endl;
                protocol.pickup(name,0, box);
            }
            continue;
        }

        if (action.compare(ACTION_READ) == 0) {
            int count = inputnum();

            while (count > 0) {
                std::cout << protocol.recvevent().parseinfo() << std::endl;
                count -= 1;
            }
            continue;
        }

        std::cerr << "NOT RECOGNIZED: " << action << std::endl;
    }
}
