#include "./lobbycontrol.h"

#include <iostream>
#include <utility>

#include "common/protocolerror.h"

LobbyControl::LobbyControl(LobbyContainer& _lobbies): lobbies(_lobbies) {}

Match& LobbyControl::handleNewClient(ControlledPlayer& player, ServerProtocol& protocol,
                                     bool* isanfitrion) {
    uint8_t playercount;
    if (!protocol.recvplayercount(&playercount)) {
        throw ProtocolError("Did not receive player count for controller!");
    }
    player.setplayercount(playercount);
    player.open();

    lobby_action info = protocol.recvlobbyaction();

    if (info.action == NEW_LOBBY) {
        *isanfitrion = true;
        return handleNewLobby(player, protocol);
    }
    *isanfitrion = false;
    return handleJoinLobby(info.attached_id, player);  //, protocol);
}

Match& LobbyControl::handleNewLobby(ControlledPlayer& player, ServerProtocol& protocol) {
    Match& newlobby = lobbies.newLobby(&player);
    std::cerr << player.toString() << " created lobby id: " << (int)newlobby.getID() << std::endl;

    // Send back lobby id.

    // And wait..
    if (protocol.recvsignalstart()) {
        lobbies.startLobby(newlobby);
        std::cerr << "Started lobby id: " << (int)newlobby.getID() << std::endl;
        return newlobby;
    }

    throw ProtocolError("Did not receive new lobby start match signal");
}

Match& LobbyControl::handleJoinLobby(unsigned int id,
                                     ControlledPlayer& player) {  //, ServerProtocol& protocol) {
    Match& joinedlobby = lobbies.joinLobby(&player, id);

    std::cerr << player.toString() << " joined lobby " << (int)joinedlobby.getID() << std::endl;
    return joinedlobby;
}
