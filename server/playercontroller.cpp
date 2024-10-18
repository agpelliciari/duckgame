#include "./playercontroller.h"

#include <iostream>
#include <utility>

#include "common/liberror.h"
#include "./gameerror.h"
#include "./playernotifier.h"


PlayerController::PlayerController(LobbyContainer& _lobbies, Socket& skt):
        lobbies(_lobbies), protocol(std::move(skt)) {}


bool PlayerController::isopen() { return isactive; }

void PlayerController::init() {
    if (_is_alive) {
        throw GameError("Tried to init player notifier/controller when already inited.");
    }
    isactive = true;
    
    start();
}

void PlayerController::playOn(Player& player, Match& match){
    player.open();
    // Inicia notifier.
    PlayerNotifier notifier(player, protocol);
    notifier.start();
    try {
        
        // Loopeado de acciones
        while (_keep_running) {
            match.notifyAction(protocol.recvpickup());
        }
        player.disconnect();  // Finalizo normalmente.
    } catch (const LibError& error) {
        if (player.disconnect() && isactive) {  // Si desconecto. Hubo error aca.
            std::cerr << "Controller lib error:" << error.what() << std::endl;
        }
    } catch (const GameError& error) {  // EOF, el notify se asume no genera exception.
        player.disconnect();
    }
    
    notifier.stop();
    notifier.join();    

    // El log a cerr podria ser innecesario. Pero sirve para hacer cosas mas descriptivas.
    std::cerr << ">closed Player " << player.getid(0) << std::endl;
    if(player.playercount() >1 ){
        std::cerr << ">closed Player " << player.getid(1) << std::endl;
    }
}
void PlayerController::run() {
    try{
    
        uint8_t playercount; 
        if(!protocol.recvplayercount(&playercount)){
            std::cerr << "Player controller aborted" << std::endl;
            return; // Permitamos que se desconecte inicialmente si no se manda el count.
        }
        
        lobby_info info =protocol.recvlobbyinfo();
        std::cerr << "Connected lobby info act " << (int) info.lobby_action << std::endl;
        
        Player player;
        player.setplayercount(playercount);
        lobbyID id = lobbies.newLobby(&player);
        playOn(player, lobbies.startLobby(id));
        
    } catch (const LibError& error) {
        std::cerr << "Lobby lib error:" << error.what() << std::endl;
    } catch (const GameError& error) {  // .
        std::cerr << "Lobby game error:" << error.what() << std::endl;
    }
    isactive = false;

    
}

// Este metodo no hace acciones irreversibles
// Tal que vos podrias re empezar los threads devuelta. Reconectar.
void PlayerController::finish() {
    // Como solo el controller modifica el keep running/llama a stop sirve
    // para saber si todavia no se termino
    if (!_keep_running) {
        return;
    }
    if(isactive){
        isactive = false;
        // Cerra forzosamente
        protocol.close();
    }
    
    stop();
    

    // Joins
    join();
}

PlayerController::~PlayerController() {
    finish();
}
