#ifndef LIB_PlayerContainer_H
#define LIB_PlayerContainer_H


#include <list>
#include <map>
#include <vector>

#include "./controlledplayer.h"
#include "common/dtosgame.h"
#include "server/logic_server/matchobserver.h"

// Contenedor/monitor de los players activos en el match.
typedef std::list<ControlledPlayer> player_container;
typedef std::map<player_id, int> ids_map;


class PlayerContainer: public MatchObserver {
private:
    player_container players;  // cppcheck-suppress unusedStructMember
    bool canceled;             // cppcheck-suppress unusedStructMember
    
    int max_players;   // cppcheck-suppress unusedStructMember
    int totalplayers;  // cppcheck-suppress unusedStructMember
    // Por ahora player last id es la cantidad de total_players+1 basicamente.
    player_id last_id;  // cppcheck-suppress unusedStructMember
    
    // Lista para que el controlled player pueda tener una referencia por mas haya cambios.
    std::list<int> ids_positions;
    
    player_container::iterator findit(const ControlId& id);

public:
    // Default constructor
    PlayerContainer(const int _max_players);
    // No copy nor mov.
    PlayerContainer(const PlayerContainer&) = delete;
    PlayerContainer& operator=(const PlayerContainer&) = delete;
    PlayerContainer(PlayerContainer&&) = delete;
    PlayerContainer& operator=(PlayerContainer&&) = delete;

    // Es necesrio trabajar con punteros al ser una coleccion
    void add(ControlId& id_out);
    bool remove(const ControlId& player);
    ControlledPlayer& get(const ControlId& id);

    void finishLobbyMode();
    void finishWaitMode();
    void finishGameMode(const MatchStatsInfo& match_stats);

    void hostLobbyLeft(const ControlId& player);
    void cancelByError(LobbyErrorType error);

    // Remueve todos los restantes. Normalmente no deberia haber, ya se deberian haber desconectado.
    void forceDisconnectAll();

    int playercount() const override;

    std::vector<player_id> getPlayers() const override;
    void putPlayers(std::vector<player_id>& out) const;

    // Push/notifica eventos a los players, de forma no bloqueante! No tiene precondiciones perse
    // Devuelve los players que se desconectaron. Podrian ser notificados directamente
    std::vector<player_id> updateState(MatchDto& state) override;

    void notifyInfo(const lobby_info& info);
};

#endif
