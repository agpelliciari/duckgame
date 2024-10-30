#include "./game_action_sender.h"

#include <cstring>
#include <iostream>
#include <string>
#include <utility>

#include "./game_state_recv.h"
#include "common/core/liberror.h"

#define ASK_NAME "What is your name?"
#define ACTION_EXIT "Exit"
#define ACTION_PICKUP "Pickup"
#define ACTION_READ "Read"

static unsigned int inputnum() {
    unsigned int res;
    if (!(std::cin >> res)) {
        throw LibError(1, "Could not read number argument");
    }

    return res;
}


GameActionSender::GameActionSender(ClientProtocol& _protocol, EventListener& _listener):
        protocol(&_protocol), listener(_listener) {}

GameActionSender::GameActionSender(GameActionSender&& other):
        protocol(other.protocol), listener(other.listener) {
    other.protocol = NULL;
}
GameActionSender& GameActionSender::operator=(GameActionSender&& other) {
    if (protocol == other.protocol) {
        return *this;
    }

    this->protocol = other.protocol;
    other.protocol = NULL;

    this->listener = other.listener;

    return *this;
}

void GameActionSender::disconnect() { std::cout << "SHOULD SEND DISCCONNECT!" << std::endl; }
void GameActionSender::doaction(const PlayerActionDTO& action) { actions.try_push(action); }

bool GameActionSender::isrunning() { return _is_alive; }

void GameActionSender::listenStdin() {
    // Por ahora alguna especie de mock en envio de acciones.
    std::string action;
    // Simple listen de acciones.
    std::cout << "LISTEN STDIN " << std::endl;
    while (_keep_running && std::cin >> action) {
        if (action.compare(ACTION_EXIT) == 0) {
            std::cout << "EXIT " << action << std::endl;
            return;
        }

        if (action.compare(ACTION_READ) == 0) {
            std::cout << "READ " << action << std::endl;
            int count = inputnum();

            while (count > 0) {
                std::cout << protocol->recvstate().parse() << std::endl;
                count -= 1;
            }
            continue;
        }
        std::cout << "MOVE " << action << std::endl;
        char* act = action.data();
        int left = action.length();
        int ind = 0;
        while (ind < left) {
            sendMove(*(act + ind));
            ind++;
        }
    }
}
void GameActionSender::begin() {
    if (is_alive()) {
        std::cerr << "ALREADY STARTED SENDER!\n";
        return;
    }
    std::cout << "GOT TO BEGIN GAME SENDER?! " << protocol << std::endl;
    start();
}

void GameActionSender::end() {
    std::cout << "ENDING GAME SENDER!!\n";
    if (_keep_running) {
        stop();
        actions.close();
        join();
    }
}


void GameActionSender::sendMove(char action) {

    PlayerActionDTO dto;
    if (action == 'a') {
        dto.playerind = 0;
        dto.type = MOVE_LEFT;
    } else if (action == 'd') {
        dto.playerind = 0;
        dto.type = MOVE_RIGHT;
    } else if (action == 'j') {
        dto.playerind = 1;
        dto.type = MOVE_LEFT;
    } else if (action == 'l') {
        dto.playerind = 1;
        dto.type = MOVE_RIGHT;
    } else {
        return;
    }
    doaction(dto);
}

void GameActionSender::run() {

    try {
        GameStateRecv receiver(*protocol, listener);
        receiver.start();

        while (_keep_running) {
            PlayerActionDTO dto = actions.pop();
            // std::cout << "POP.. SEND Player ACTION? " << (int)dto.type << " " <<
            // (int)dto.playerind
            //           << std::endl;
            protocol->sendaction(dto);
            // std::cout << "ALO SEND ACTION?" << std::endl;
        }
    } catch (const ClosedQueue& error) {
        std::cerr << "Game action sender closed!" << std::endl;
        // protocol.close();  // Si no esta cerrado, cerralo, asi se sale el controller tambien.
    } catch (const LibError&
                     error) {  // No deberia pasara realmente, antes pasaria en el controller.
        std::cerr << "sender error: " << error.what() << std::endl;
    }
}


bool GameActionSender::endstate() { return true; }

GameActionSender::~GameActionSender() { end(); }
