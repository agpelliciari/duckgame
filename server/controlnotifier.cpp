#include "./controlnotifier.h"

#include <iostream>

#include "common/core/liberror.h"

ControlNotifier::ControlNotifier(ControlledPlayer& _player, ServerProtocol& _protocol):
        player(_player), protocol(_protocol) {}

void ControlNotifier::run() {
    try {
        while (_keep_running) {
            protocol.sendstate(player.popstate());
        }

    } catch (const ClosedQueue& error) {
        protocol.close();  // Si no esta cerrado, cerralo, asi se sale el controller tambien.
    } catch (const LibError&
                     error) {     // No deberia pasara realmente, antes pasaria en el controller.
        if (protocol.isopen()) {  // Si en teoria esta abierto...
            std::cerr << "player " << player.getid(0) << " notify error: " << error.what()
                      << std::endl;

            // El cerrar no deberia estar aca capaz. Si fallo el send otro fallara tmbn
        }
    }
}

ControlNotifier::~ControlNotifier() {
    stop();
    player.disconnect();  // Por si no se cerro, cerra la queue.
    join();
}
