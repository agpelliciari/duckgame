#ifndef LIB_PlayerContainer_H
#define LIB_PlayerContainer_H


#include <list>
#include <vector>

#include "./controlledplayer.h"
#include "common/dtosgame.h"
#include "server/logic_server/matchobserver.h"

// Contenedor/monitor de los players activos en el match.
class PlayerContainer: public MatchObserver {
public:
    typedef std::list<ControlledPlayer> player_container;

private:
    player_container players;  // cppcheck-suppress unusedStructMember
    bool canceled;             // cppcheck-suppress unusedStructMember

    int totalplayers;  // cppcheck-suppress unusedStructMember
    // Por ahora player last id es la cantidad de total_players+1 basicamente.
    player_id last_id;  // cppcheck-suppress unusedStructMember
public:
    // Default constructor
    PlayerContainer();
    // No copy nor mov.
    PlayerContainer(const PlayerContainer&) = delete;
    PlayerContainer& operator=(const PlayerContainer&) = delete;
    PlayerContainer(PlayerContainer&&) = delete;
    PlayerContainer& operator=(PlayerContainer&&) = delete;

    // Es necesrio trabajar con punteros al ser una coleccion
    ControlledPlayer& add(uint8_t countplayers);
    void remove(const ControlledPlayer& player);

    void finishLobbyMode();
    void finishGameMode();

    void hostLobbyLeft(const ControlledPlayer& player);
    void cancelByError(LobbyErrorType error);

    // Remueve todos los restantes. Normalmente no deberia haber, ya se deberian haber desconectado.
    void forceDisconnectAll();

    int playercount() const override;

    std::vector<player_id> getPlayers() override;

    // Push/notifica eventos a los players, de forma no bloqueante! No tiene precondiciones perse
    // Devuelve los players que se desconectaron. Podrian ser notificados directamente
    std::vector<player_id> updateState(const MatchDto& state) override;

    void notifyInfo(const lobby_info& info);
};

#endif
