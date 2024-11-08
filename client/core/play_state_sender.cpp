#include <cstring>
#include <iostream>
#include <string>
#include <utility>

#include "./game_action_sender.h"
#include "./game_state_recv.h"
#include "common/core/liberror.h"

GameActionSender::GameActionSender(Messenger& _messenger, EventListener& _listener,
                                   GameContext& _context):
        protocol(_messenger),
        listener(_listener),
        context(_context),
        firstidle(true),
        secondidle(true) {}

/*
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
*/

void GameActionSender::disconnect() { std::cout << "SHOULD SEND DISCCONNECT!" << std::endl; }
void GameActionSender::doaction(const PlayerActionDTO& action) {

    if (action.playerind != 0 && !context.dualplay) {
        return;
    }


    actions.try_push(action);
}

bool GameActionSender::isrunning() { return _is_alive; }

void GameActionSender::begin() {
    if (is_alive()) {
        // std::cerr << "ALREADY STARTED SENDER!\n";
        return;
    }
    // std::cout << "GOT TO BEGIN GAME SENDER?! " << protocol << std::endl;
    start();
}

void GameActionSender::end() {
    if (_keep_running) {
        std::cout << "ENDING GAME SENDER!!\n";
        stop();
        actions.close();
        join();
    }
}

void GameActionSender::run() {

    try {
        GameStateRecv receiver(protocol, listener);
        receiver.start();

        while (_keep_running) {
            PlayerActionDTO dto = actions.pop();
            protocol.sendaction(dto);
        }
    } catch (const ClosedQueue& error) {
        std::cerr << "Game action sender closed!" << std::endl;
        // protocol.close();  // Si no esta cerrado, cerralo, asi se sale el controller tambien.
    } catch (const LibError&
                     error) {  // No deberia pasara realmente, antes pasaria en el controller.
        std::cerr << "sender error: " << error.what() << std::endl;
    }
}


bool GameActionSender::endstate() {
    end();
    return true;
}

GameActionSender::~GameActionSender() { end(); }
