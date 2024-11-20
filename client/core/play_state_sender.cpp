#include "./play_state_sender.h"

#include <cstring>
#include <iostream>
#include <string>
#include <utility>

#include "./play_state_recv.h"
#include "common/core/liberror.h"

PlayStateSender::PlayStateSender(Messenger& _messenger, EventListener& _listener,
                                 GameContext& _context):
        protocol(_messenger),
        listener(_listener),
        context(_context),
        firstidle(true),
        secondidle(true) {}

void PlayStateSender::disconnect() { std::cout << "SHOULD SEND DISCCONNECT!" << std::endl; }

void PlayStateSender::doaction(const PlayerActionDTO& action) {

    if (action.playerind != 0 && !context.dualplay) {
        return;
    }


    actions.try_push(action);
}

bool PlayStateSender::isrunning() { return _is_alive; }

void PlayStateSender::begin() {
    if (is_alive()) {
        // std::cerr << "ALREADY STARTED SENDER!\n";
        return;
    }
    // std::cout << "GOT TO BEGIN GAME SENDER?! " << protocol << std::endl;
    start();
}

void PlayStateSender::end() {
    if (_keep_running) {
        std::cout << "ENDING GAME SENDER!!\n";
        stop();
        actions.close();
        join();
    }
}

void PlayStateSender::run() {

    try {
        PlayStateRecv receiver(protocol, listener, context);
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


bool PlayStateSender::endstate() {
    end();
    return true;
}

PlayStateSender::~PlayStateSender() { end(); }
