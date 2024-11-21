#include "./lobbycontrol.h"

#include <iostream>
#include <utility>
#include <vector>

#include "./gameerror.h"
#include "common/core/liberror.h"
#include "common/protocolerror.h"
#include "common/serialerror.h"

LobbyControl::LobbyControl(LobbyContainer& _lobbies, ServerProtocol& _protocol):
        lobbies(_lobbies), protocol(_protocol) {}



Match& LobbyControl::resolveJoin(ControlId& outPlayer){
    
    // Todo en un metodo para que sea thread safe.
    // Podria tener info extra. Ahora es medio lo mismo que el size nada mas.
    std::vector<player_id> players;
    Match& joined = lobbies.joinLobby(protocol.recvlobbyid(), outPlayer, players);

    // Si no hubo error.. ahora notifica el join. El player_id no es conocido por protocol.
    protocol.notifyinfo(LobbyResponseType::JOINED_LOBBY, players.size());
    
    return joined;
}

Match& LobbyControl::resolveHost(ControlId& outPlayer){
    Match& newlobby = lobbies.newLobby(outPlayer);
    std::cerr << " created lobby id: " << (int)newlobby.getID() << std::endl;
    // Send back id...
    protocol.notifyid(newlobby.getID());
    
    protocol.sendmaplist(lobbies.registeredMaps());
    
    return newlobby;
}


Match& LobbyControl::resolveMatch(bool& ishost,ControlId& outPlayer) {
    LobbyActionType action = protocol.recvresolveinfo();
    ishost = action == CREATE_LOBBY; 
    
    // Primero se envia el playercount, sea join o no.
    outPlayer.setcount(protocol.recvplayercount()); 
    
    return ishost? resolveHost(outPlayer) : resolveJoin(outPlayer);
}

void LobbyControl::notifyPlayer(const ControlledPlayer& player){
     int pos = player.getpos();
     protocol.notifyid(pos);
     
     if(player.playercount() == 2){
         protocol.notifyid(pos+1);
     }
}


bool LobbyControl::handleAnfitrionLobby(ControlledPlayer& host,
                                        Match& match) {  // ControlledPlayer& player,
    try {
        // And wait..
        LobbyActionType action(protocol.recvlobbyaction());

        while (action != LobbyActionType::PLAYER_READY) {
            // Handlea accion! Si hay que hacer algo. i.e obtene info en base al tipo
            std::cerr << "RECEIVED ACTION NON READY?" << std::endl;
            action = protocol.recvlobbyaction();
        }

        std::string map = protocol.recvmapname();
        lobbies.startLobby(match, map.c_str());
        std::cerr << "Started MATCH id: " << (int)match.getID() << " WITH: " << match.playercount()
                  << std::endl;
        return false;
    } catch (const ProtocolError& error) {
        // EOF of player. No muestres nada.
        std::cerr << "CANCELED MATCH ID: " << error.what() << " " << (int)match.getID()<< std::endl;
                  
        protocol.close();
        lobbies.hostLeft(match, host);
        return true;
    } catch (const LibError& error) {
        if (protocol.isactive()) {  // Si debiera estar activo. Error interno del protocol.
            std::cerr << "Lobby control error:" << error.what() << std::endl;
            protocol.close();
        }
        std::cerr << "Cancel lobby?:" << error.what()<< std::endl;
        lobbies.hostLeft(match, host);
        return true;
    } catch (const SerialError& error) {
        std::cerr << "Map load error?:" << error.what() << std::endl;
        lobbies.errorOnLobby(match, MAP_INVALID);
        return true;
    } catch (const GameError& error) {
        // Fallo alguna accion. Sea el start u otra.
        std::cerr << "Game error at host lobby recv: " << error.what() << std::endl;
        lobbies.errorOnLobby(match, error.get_code());
        return true;
    }
}
