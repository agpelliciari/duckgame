#include "./playernotifier.h"

#include <iostream>

#include "common/event.h"
#include "common/liberror.h"
#include "common/queue.h"

PlayerNotifier::PlayerNotifier(Player& _player, PlayerProtocol& _protocol):
        player(_player), protocol(_protocol) {}

void PlayerNotifier::sendevent(const Event&& event) {
    if (event.type() == NEW_BOX) {
        protocol.notifynewbox();
        return;
    }

    // Asegurado es PICK UP por ahora.
    protocol.notifypickup(event.actor(), event.attachedID());
}

void PlayerNotifier::run() {
    try {
        while (_keep_running) {
            sendevent(player.popevent());
        }

    } catch (const ClosedQueue& error) {
        // Simplemente se cerro el notifier. Por ahora no se necesita mas.

    } catch (const LibError&
                     error) {       // No deberia pasara realmente, antes pasaria en el controller.
        if (player.disconnect()) {  // Si no estaba desconectado...
            std::cerr << "player " << player.getid(0) << " notify error: " << error.what()
                      << std::endl;
        }
    }
}
