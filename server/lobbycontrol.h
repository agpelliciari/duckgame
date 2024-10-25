#ifndef LIB_LobbyControl_H
#define LIB_LobbyControl_H


#include "./controlledplayer.h"
#include "./lobbycontainer.h"
#include "./match.h"
#include "common/serverprotocol.h"

class LobbyControl {
    // typedef void (LobbyControl::* lobby_proc)();
protected:
    LobbyContainer& lobbies;   // cppcheck-suppress unusedStructMember
    ControlledPlayer& player;  // cppcheck-suppress unusedStructMember

    // Podria encapsularse en una clase y usar heap...
    // o usar los punteros a funcion... pero vale la pena?!
    bool isanfitrion;  // cppcheck-suppress unusedStructMember

    // Que sea un puntero para evitar problemas con constructores.
    Match* match;  // cppcheck-suppress unusedStructMember

    bool handleNewClient(ServerProtocol& protocol);


public:
    // Crea el player con el ide pasado e inicia el protocolo
    // explicit LobbyControl(LobbyContainer& _lobbies, ControlledPlayer& _player);
    explicit LobbyControl(LobbyContainer& _lobbies, ControlledPlayer& _player,
                          ServerProtocol& protocol);

    // Por ahora tambien nos escapamos del move.
    LobbyControl(LobbyControl&&) = delete;
    LobbyControl& operator=(LobbyControl&&) = delete;

    // Asumamos por ahora que no se quiere permitir copias
    LobbyControl(const LobbyControl&) = delete;
    LobbyControl& operator=(const LobbyControl&) = delete;


    void doaction(ServerProtocol& protocol);
    bool start(ServerProtocol& protocol);


    ~LobbyControl();
};

#endif
