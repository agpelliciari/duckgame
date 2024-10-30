#ifndef LIB_ServerProtocol_H
#define LIB_ServerProtocol_H

#define BUFF_LEN_CLIENT 128
#include <atomic>
#include <string>
#include <utility>

#include "common/core/protocol.h"
#include "common/dtos.h"
#include "common/dtosplayer.h"

// Extension del protocolo base a usar.
class ServerProtocol {

protected:
    Protocol protocol;  // Composicion con el protocolo base para la conexion

    std::atomic<bool> isactive;  // Simple manejo de si ya se cerro o no.

public:
    // El default a partir de la abstraccion de socket..
    explicit ServerProtocol(Socket& messenger);
    explicit ServerProtocol(Messenger* messenger);

    // Permitamos el mov para mayor flexibilidad
    explicit ServerProtocol(Protocol&& prot);

    // Asumamos por ahora que no se quiere permitir copias, ni mov.
    ServerProtocol(const ServerProtocol&) = delete;
    ServerProtocol& operator=(const ServerProtocol&) = delete;

    ServerProtocol(ServerProtocol&&) = delete;
    ServerProtocol& operator=(ServerProtocol&&) = delete;

    uint8_t recvplayercount();

    bool recvlobbyinfo(lobby_info& out);
    void notifyid(uint8_t id);

    bool recvsignalstart();


    void notifyaction(const LobbyActionType action);
    void notifyinfo(const LobbyActionType action, const uint8_t attached_id);

    // Attempts to receive pickup action.
    // If failed throws either LibError or GameError.
    PlayerActionDTO recvaction();

    void sendstate(const MatchDto&& state);
    void sendstate(const MatchDto& state);

    bool isopen();
    void close();
};

#endif
