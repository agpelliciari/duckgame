#include "./clientprotocol.h"

#include <iostream>
#include <string>
#include <utility>

#include "../common_src/event.h"
#include "../common_src/liberror.h"
#include "../common_src/reward.h"

ClientProtocol::ClientProtocol(Socket skt): protocol(skt) {}

void ClientProtocol::pickup(const std::string& name, const uint8_t box) {
    protocol.signalpickup();
    protocol.sendmsg(name);
    protocol.sendbyte(box);
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
