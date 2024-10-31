#ifndef MOCK_OBSERVER
#define MOCK_OBSERVER

#include <vector>

#include "./testermatchdto.h"
#include "server/logic_server/matchobserver.h"

class MockObserver: public TesterMatchDTO, public MatchObserver {
private:
    std::vector<player_id> players;  // cppcheck-suppress unusedStructMember

public:
    explicit MockObserver(const MatchDto& firstUpdate, const int count);

    void assertHasAllPlayers();


    int playercount() const override;

    std::vector<player_id> getPlayers() override;


    // Push/notifica eventos a los players, de forma no bloqueante! No tiene precondiciones perse
    // Devuelve los players que se desconectaron. Podrian ser notificados directamente
    std::vector<player_id> updateState(const MatchDto& state) override;
};

#endif
