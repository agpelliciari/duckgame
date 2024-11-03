#include "./controlreceiver.h"

#include <iostream>
#include <utility>

#include "./controlnotifier.h"
#include "./gameerror.h"
#include "./lobbycontrol.h"
#include "common/core/liberror.h"
#include "common/protocolerror.h"


ControlReceiver::ControlReceiver(LobbyContainer& _lobbies, Socket& _skt):
        lobbies(_lobbies), skt(std::move(_skt)), protocol(skt) {}


bool ControlReceiver::isopen() { return protocol.isactive(); }

void ControlReceiver::init() {
    if (_is_alive) {
        throw GameError("Tried to init player notifier/controller when already inited.");
    }
    start();
}
void ControlReceiver::playOn(const ControlledPlayer& player, Match& match) {
    try {
        // std::cout << "PLAY ON " << std::endl;
        //  Loopeado de acciones
        while (_keep_running) {
            PlayerActionDTO action = protocol.recvaction();
            if (player.playercount() <= action.playerind) {
                std::cerr << "Invalid action from client!!\n";
                continue;
            }
            action.playerind = player.getid(action.playerind);
            match.notifyAction(action);
        }
    } catch (const ProtocolError& error) {
        // std::cout << "-->EOF? closed? " << (int)protocol.isactive() << " " << error.what() <<
        // std::endl;
        //   std::endl; EOF of player. No muestres nada. Pero si el protocol esta abierto, significa
        //   el cliente se desconecto.
    } catch (const LibError& error) {
        if (protocol.isactive()) {  // Si debiera estar activo. Error interno del protocol.
            std::cerr << "Controller lib error:" << error.what() << std::endl;
        }
    } catch (const std::exception& err) {
        std::cerr << "excep : " << err.what() << " Ending control receiver.\n";
    } catch (...) {
        std::cerr << "excep <unknown> Ending control receiver.\n";
    }
}
void ControlReceiver::run() {
    try {
        LobbyControl lobby(lobbies, protocol);

        bool isanfitrion;
        Match& match = lobby.resolveMatch(&isanfitrion);
        ControlledPlayer& player = lobby.joinPlayers(match);
        // Inicia notifier.
        ControlNotifier notifier(match, player, protocol);
        notifier.start();

        if (isanfitrion && lobby.handleAnfitrionLobby(player, match)) {
            return;  // No se empezo la partida.
        }

        // Si no es el anfitrion que ya asuma empezo. Total no deberia mandar nada
        // En la fase de lobby, solo podria irse. Para lo que esta disconnect despues
        playOn(player, match);
        lobbies.disconnectFrom(match, player);

    } catch (const GameError& error) {
        std::cerr << "Game error at lobby: " << error.what() << std::endl;
        // Por ahora unknown... pero a futuro se agregara al error.
        protocol.notifyinfo(LobbyResponseType::GAME_ERROR, LobbyErrorType::UNKNOWN);
    }
}

// Este metodo no hace acciones irreversibles
// Tal que vos podrias re empezar los threads devuelta. Reconectar.
void ControlReceiver::finish() {
    // Como solo el controller modifica el keep running/llama a stop sirve
    // para saber si todavia no se termino
    if (!_keep_running) {
        return;
    }

    // Se encarga el protocol de verificar solo sea cerrado una vez.
    protocol.close();

    stop();


    // Joins
    join();
}

ControlReceiver::~ControlReceiver() { finish(); }
