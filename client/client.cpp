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
    
    int countplayers = 1;
    if(name2.size() > 0){
       std::cerr << "2 players: "<< name << " " << name2 << std::endl;
       countplayers = 2;
    } else{
       std::cerr << "1 player: "<< name << std::endl;
    }
    
    std::cerr << "new lobby?[y|n]: " << std::endl;
    
    std::string action;
    if (!(std::cin >> action)) {  // Could not read if new lobby.
        throw LibError(1, "Could not read if new lobby was desired!");
    }
    
    if(action.size() != 1 || (*action.c_str() != 'y')){
        std::cerr << "lobby id to join: " << std::endl;
        uint8_t lobbyid = inputnum();  // Se valida en el server.
        protocol.joinLobby(countplayers, lobbyid);
    } else{
        protocol.createLobby(countplayers);
        std::cerr << "press enter to start the match!" << std::endl;
        if (!(std::cin >> action)) {  // Could not read if new lobby.
            throw LibError(1, "Did not read match start!!");
        }
        
        protocol.startlobby();
    }
    
    while (std::cin >> action) {
        if (action.compare(ACTION_EXIT) == 0) {
            return;
        }
        if (action.compare(ACTION_PICKUP) == 0) {
            uint8_t indplayer = inputnum();  // Se valida en el server.
            uint8_t box = inputnum();  // Se valida en el server.
            
            if(indplayer == 1 &&  countplayers > 1){
                std::cerr << "Picked up " << name2 <<" box: "<< (int)box << std::endl;
                protocol.pickup(1, box);
            } else{
                std::cerr << "Picked up " << name <<" box: "<< (int)box << std::endl;
                protocol.pickup(0, box);
            }
            continue;
        }

        if (action.compare(ACTION_READ) == 0) {
            int count = inputnum();

            while (count > 0) {
                std::cout << protocol.recvstate().parse() << std::endl;
                count -= 1;
            }
            continue;
        }

        std::cerr << "NOT RECOGNIZED: " << action << std::endl;
    }
}
