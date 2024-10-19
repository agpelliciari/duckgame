#include "./playernotifier.h"

#include <iostream>

#include "common/event.h"
#include "common/liberror.h"
#include "common/queue.h"

PlayerNotifier::PlayerNotifier(ControlledPlayer& _player, PlayerProtocol& _protocol):
        player(_player), protocol(_protocol) {}

void PlayerNotifier::run() {
    try {
        while (_keep_running) {
            protocol.sendstate(player.popstate());
        }

    } catch (const ClosedQueue& error) {
        // Simplemente se cerro el notifier. Por ahora no se necesita mas.
        protocol.close();  // Si no esta cerrado, cerralo, asi se sale el controller tambien.
    } catch (const LibError&
                     error) {       // No deberia pasara realmente, antes pasaria en el controller.
        if (player.disconnect()) {  // Si no estaba desconectado...
            std::cerr << "player " << player.getid(0) << " notify error: " << error.what()
                      << std::endl;
        }
    }
}
