#ifndef LIB_ServerProtocol_H
#define LIB_ServerProtocol_H

#define BUFF_LEN_CLIENT 128
#include <atomic>
#include <string>
#include <utility>

#include "common/core/protocol.h"
#include "common/dtosgame.h"
#include "common/dtoslobby.h"
#include "common/dtosmap.h"


// Extension del protocolo base a usar.
class ServerProtocol: public Protocol {
public:
    // El default a partir de la abstraccion de socket..
    explicit ServerProtocol(Messenger& messenger);

    // Asumamos por ahora que no se quiere permitir copias, ni mov.
    ServerProtocol(const ServerProtocol&) = delete;
    ServerProtocol& operator=(const ServerProtocol&) = delete;

    ServerProtocol(ServerProtocol&&) = delete;
    ServerProtocol& operator=(ServerProtocol&&) = delete;

    // Lobby protocol..
    // Filtra el tipo de accion. Si bien se podrian tener separadas.
    LobbyActionType recvresolveinfo();
    // Para el join
    uint8_t recvlobbyid();

    // Para ambos, create o join.
    uint8_t recvplayercount();

    // Para el create
    void notifyid(uint8_t id);

    // Acciones/Respuestas
    LobbyActionType recvlobbyaction();
    std::string recvmapname();

    void notifyaction(const LobbyResponseType response);
    void notifyinfo(const LobbyResponseType response, const uint8_t data);
    void notifyevent(const lobby_info& info);

    // Info nivel
    // void sendlevel(const LevelInfo& level);

    // Game protocol
    PlayerActionDTO recvaction();

    void sendstate(const MatchDto&& state);
    void sendstate(const MatchDto& state);

    void sendplayer(const PlayerDTO& player);

    void sendmapinfo(const MapInfo& map);

    // metodos generales para is active.
    using Protocol::close;
    using Protocol::isactive;
};

#endif
