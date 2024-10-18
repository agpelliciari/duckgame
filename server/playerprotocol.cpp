#include "./playerprotocol.h"

#include <iostream>
#include <string>
#include <utility>

#include "common/event.h"
#include "./gameerror.h"


PlayerProtocol::PlayerProtocol(Socket&& skt): protocol(skt), isactive(true) {}

bool PlayerProtocol::recvplayercount(uint8_t* count){
    return protocol.tryrecvbyte(count);
}

bool PlayerProtocol::recvsignalstart(){
    uint8_t sign;
    if(protocol.tryrecvbyte(&sign)){
         return (LobbyActionType)(sign) == LobbyActionType::STARTED_LOBBY;
    }
    
    return false;
}





lobby_info PlayerProtocol::recvlobbyinfo(){
     lobby_info out;
     protocol.recvbytes(&out, sizeof(out));
     return out;
}

MatchAction PlayerProtocol::recvpickup() {
    if (!protocol.recvpickup()) {
        throw GameError("Could not receive pickup.");
    }
    uint8_t indx = protocol.recvbyte();
    std::string name = protocol.recvmsgstr();
    name.append(std::to_string(indx));
    
    // -1 ya que el cliente va de caja 1 a 4.. En el server es de 0 a 3.
    return MatchAction(name, protocol.recvbyte() - 1);
}

void PlayerProtocol::notifypickup(const std::string& player, const uint8_t box) {
    protocol.notifyevent(EventType::PICKUP);

    protocol.sendmsg(player);
    protocol.sendbyte(box);
}
void PlayerProtocol::notifynewbox() { protocol.notifyevent(EventType::NEW_BOX); }

bool PlayerProtocol::isopen(){
     return isactive.load();
}

void PlayerProtocol::close() { 
    if(isactive.exchange(false)){
       protocol.close();
    }
}
