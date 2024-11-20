#ifndef MOCK_OBSERVER
#define MOCK_OBSERVER

#include <vector>

#include "server/logic_server/match_state.h"
#include "server/logic_server/matchobserver.h"
#include "tests/core/testermatchdto.h"


class MockObserver: public TesterMatchDTO, public MatchObserver {
private:
    std::vector<player_id> players;  // cppcheck-suppress unusedStructMember

public:
    explicit MockObserver(const MatchDto& firstUpdate, const int count);

    const PlayerDTO* getPlayer(int id) const;

    void assertPlayerMovedLeft(const PlayerDTO* playerGiven, const PlayerDTO* playerBase);
    void assertPlayerMovedRight(const PlayerDTO* playerGiven, const PlayerDTO* playerBase);

    void assertPlayerMovedHigher(const PlayerDTO* playerGiven, const PlayerDTO* playerBase);
    void assertPlayerMovedAirRight(const PlayerDTO* playerGiven, const PlayerDTO* playerBase);
    void assertPlayerMovedAirLeft(const PlayerDTO* playerGiven, const PlayerDTO* playerBase);

    void assertHasAllPlayers();

    // Sends action pide actualizar y retorna estado anterior.
    MatchDto sendActionAndUpdate(MatchState& match, const PlayerActionType& _type,
                                 uint8_t _playerind);


    int playercount() const override;

    std::vector<player_id> getPlayers() const override;


    // Push/notifica eventos a los players, de forma no bloqueante! No tiene precondiciones perse
    // Devuelve los players que se desconectaron. Podrian ser notificados directamente
    std::vector<player_id> updateState(const MatchDto& state) override;
};

#endif
