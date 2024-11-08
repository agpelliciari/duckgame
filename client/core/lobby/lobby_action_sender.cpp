#include <iostream>

#include "./lobby_action_listener.h"
#include "common/core/liberror.h"


LobbyActionListener::LobbyActionListener(ClientProtocol& _protocol, LobbyClientSender& _actions):
        protocol(_protocol), actions(_actions) {}
void LobbyActionListener::begin() { start(); }

void LobbyActionListener::run() {
    try {
        while (_keep_running) {
            protocol.sendlobbyaction(actions.popaction());
        }
    } catch (const ClosedQueue& error) {
        std::cout << "Closed lobby sender" << std::endl;
    }
}

LobbyActionListener::~LobbyActionListener() {
    if (_keep_running) {
        stop();
        actions.close();
        join();
    }
}
