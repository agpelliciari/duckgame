#include "./lobby_action_sender.h"

#include <iostream>

#include "common/core/liberror.h"


LobbyActionSender::LobbyActionSender(ClientProtocol& _protocol, LobbyActionQueue& _actions):
        protocol(_protocol), actions(_actions) {}
void LobbyActionSender::begin() { start(); }

void LobbyActionSender::run() {
    try {
        while (_keep_running) {

            lobby_action action = actions.popaction();


            protocol.sendlobbyaction(action);

            if (action.type == PLAYER_READY) {
                std::string random(actions.randomMapLabel());
                std::string name(actions.getMapName());
                
                if (random == name){
                    name = ""; // Empty map para el server es el random.
                }
            
                protocol.sendmapname(name);
                break;
            }
        }
    } catch (const ClosedQueue& error) {
        std::cout << "Closed lobby sender" << std::endl;
    }
}

LobbyActionSender::~LobbyActionSender() {
    if (_keep_running) {
        stop();
        actions.close();
        join();
    }
}
