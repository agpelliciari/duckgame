#include "client/clientprotocol.h"

#include <iostream>
#include <string>
#include <utility>

#include "common/dtos.h"
#include "common/liberror.h"

#include "common/event.h"
#include "common/reward.h"

ClientProtocol::ClientProtocol(Socket skt): protocol(skt) {}

void ClientProtocol::pickup(const std::string& name, const uint8_t box) {
    protocol.signalpickup();
    protocol.sendmsg(name);
    protocol.sendbyte(box);
}

void ClientProtocol::joinLobby(const uint8_t playercount, const uint8_t id_match){    
    
    protocol.sendbyte(playercount); // Primero se envia el player count.
    
    // Despues info de la lobby.
    lobby_info info = {LobbyActionType::JOIN_LOBBY, id_match};
    protocol.sendbytes(&info, sizeof(info));
}
void ClientProtocol::createLobby(const uint8_t playercount){
    protocol.sendbyte(playercount);
    
    // Default 0 como mapa... que es reservado para que sea al azar.
    lobby_info info = {LobbyActionType::NEW_LOBBY, 0}; 
    protocol.sendbytes(&info, sizeof(info));
}


Event ClientProtocol::recvevent() {

    uint8_t type = protocol.recvnotification();
    if (type == EventType::NEW_BOX) {
        return Event();
    }

    if (type != EventType::PICKUP) {
        throw LibError(1, "Received notification type is invalid %d ", (int)type);
    }

    std::string name = protocol.recvmsgstr();
    return Event(name, (RewardType)protocol.recvbyte());
}
