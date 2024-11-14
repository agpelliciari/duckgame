#include "./mockobserver.h"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

using ::testing::Contains;


MockObserver::MockObserver(const MatchDto& firstUpdate, const int count):
        TesterMatchDTO(firstUpdate), players() {
    players.reserve(count);
    for (int i = 0; i < count; i++) {
        players[i] = i + 1;
    }
}


// Asserting!
void MockObserver::assertHasAllPlayers() {

    ASSERT_EQ(curr_state.players.size(), players.size()) << "Last update player count is right";

    std::vector<player_id> given;

    given.reserve(curr_state.players.size());

    for (const PlayerDTO& player: curr_state.players) {

        // Por ahora NO!
        //  cppcheck-suppress useStlAlgorithm
        given.push_back(player.id);
    }

    for (player_id id: players) {
        EXPECT_THAT(given, Contains(id)) << "Last update contains id " << (int)id;
    }
}


// Inteface..

int MockObserver::playercount() const { return players.size(); }

std::vector<player_id> MockObserver::getPlayers() { return std::vector<player_id>(players); }

// Push/notifica eventos a los players, de forma no bloqueante! No tiene precondiciones perse
// Devuelve los players que se desconectaron. Podrian ser notificados directamente
std::vector<player_id> MockObserver::updateState(const MatchDto& state) {
    curr_state = state;
    return std::vector<player_id>();
}
