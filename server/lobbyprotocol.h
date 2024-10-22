#ifndef LIB_LobbyProtocol_H
#define LIB_LobbyProtocol_H


#include "./controlledplayer.h"
#include "./lobbycontainer.h"
#include "./match.h"
#include "common/serverprotocol.h"

class LobbyProtocol {
    // typedef void (LobbyProtocol::* lobby_proc)();
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
    // explicit LobbyProtocol(LobbyContainer& _lobbies, ControlledPlayer& _player);
    explicit LobbyProtocol(LobbyContainer& _lobbies, ControlledPlayer& _player,
                           ServerProtocol& protocol);

    // Por ahora tambien nos escapamos del move.
    LobbyProtocol(LobbyProtocol&&) = delete;
    LobbyProtocol& operator=(LobbyProtocol&&) = delete;

    // Asumamos por ahora que no se quiere permitir copias
    LobbyProtocol(const LobbyProtocol&) = delete;
    LobbyProtocol& operator=(const LobbyProtocol&) = delete;


    void doaction(ServerProtocol& protocol);
    bool start(ServerProtocol& protocol);


    ~LobbyProtocol();
};

#endif
