#include "./playerprotocol.h"

#include <iostream>
#include <string>
#include <utility>

#include "common/event.h"
#include "./gameerror.h"


PlayerProtocol::PlayerProtocol(Socket&& skt): protocol(skt) {}


MatchAction PlayerProtocol::recvpickup() {
    if (!protocol.recvpickup()) {
        throw GameError(0, "Could not receive pickup.");
    }
    std::string name = protocol.recvmsgstr();
    // -1 ya que el cliente va de caja 1 a 4.. En el server es de 0 a 3.
    return MatchAction(name, protocol.recvbyte() - 1);
}

void PlayerProtocol::notifypickup(const std::string& player, const uint8_t box) {
    protocol.notifyevent(EventType::PICKUP);

    protocol.sendmsg(player);
    protocol.sendbyte(box);
}
void PlayerProtocol::notifynewbox() { protocol.notifyevent(EventType::NEW_BOX); }

void PlayerProtocol::close() { protocol.close(); }
