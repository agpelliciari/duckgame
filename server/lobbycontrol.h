#ifndef LIB_LobbyControl_H
#define LIB_LobbyControl_H


#include "./controlledplayer.h"
#include "./lobbycontainer.h"
#include "./match.h"
#include "common/serverprotocol.h"

class LobbyControl {
    // typedef void (LobbyControl::* lobby_proc)();
protected:
    LobbyContainer& lobbies;  // cppcheck-suppress unusedStructMember


    Match& handleNewLobby(ControlledPlayer& player, ServerProtocol& protocol);
    Match& handleJoinLobby(unsigned int id,
                           ControlledPlayer& player);  //, ServerProtocol& protocol);

public:
    // Crea el player con el ide pasado e inicia el protocolo
    explicit LobbyControl(LobbyContainer& _lobbies);

    // Por ahora tambien nos escapamos del move.
    LobbyControl(LobbyControl&&) = delete;
    LobbyControl& operator=(LobbyControl&&) = delete;

    // Asumamos por ahora que no se quiere permitir copias
    LobbyControl(const LobbyControl&) = delete;
    LobbyControl& operator=(const LobbyControl&) = delete;

    Match& handleNewClient(ControlledPlayer& player, ServerProtocol& protocol, bool* isanfitrion);
};

#endif
