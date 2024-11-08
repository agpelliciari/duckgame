#include "./lobby_action_sender.h"

#include <iostream>

#include "common/core/liberror.h"


LobbyActionSender::LobbyActionSender(ClientProtocol& _protocol, LobbyActionQueue& _actions):
        protocol(_protocol), actions(_actions) {}
void LobbyActionSender::begin() { start(); }

void LobbyActionSender::run() {
    try {
        while (_keep_running) {
            protocol.sendlobbyaction(actions.popaction());
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
