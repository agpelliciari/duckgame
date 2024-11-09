#include "./mockobserver.h"

#include <iostream>

#include "gmock/gmock.h"
#include "gtest/gtest.h"

using ::testing::Contains;


MockObserver::MockObserver(const MatchDto& firstUpdate, const int count):
        TesterMatchDTO(firstUpdate), players() {
    players.reserve(count);
    for (int i = 0; i < count; i++) {
        players.push_back(i + 1);
    }
}

void MockObserver::assertPlayerMovedLeft(const int id, const MatchDto& base) {
    const PlayerDTO* playerBase = base.getPlayer(id);
    if (playerBase == NULL) {
        std::cout << "NOT FOUND ID TO TEST " << id << std::endl;
        return;
    }

    std::cout << "FOUND ID TO TEST MOVE LEFT" << id << std::endl;
}
void MockObserver::assertPlayerMovedRight(const int id, const MatchDto& base) {
    const PlayerDTO* playerGiven = curr_state.getPlayer(id);
    ASSERT_TRUE(playerGiven != NULL)
            << "El player de id " << id << "estaba contenido en el curr state";

    const PlayerDTO* playerBase = base.getPlayer(id);
    if (playerBase == NULL) {
        std::cout << "NOT FOUND ID TO TEST " << id << std::endl;
        return;
    }
    std::cout << "FOUND ID TO TEST MOVE RIGHT" << id << std::endl;

    ASSERT_EQ(playerGiven->move_action, TypeMoveAction::MOVE_RIGHT)
            << "Player is currently moving right";
}

void MockObserver::assertPlayerMovedAirRight(const int id, const MatchDto& base) {
    const PlayerDTO* playerGiven = curr_state.getPlayer(id);
    ASSERT_TRUE(playerGiven != NULL)
            << "El player de id " << id << "estaba contenido en el curr state";

    const PlayerDTO* playerBase = base.getPlayer(id);
    if (playerBase == NULL) {
        std::cout << "NOT FOUND ID TO TEST " << id << std::endl;
        return;
    }
    std::cout << "FOUND ID TO TEST MOVE RIGHT" << id << std::endl;

    ASSERT_EQ(playerGiven->move_action, TypeMoveAction::AIR_RIGHT)
            << "Player is currently moving right on air";
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

MatchDto MockObserver::sendActionAndUpdate(MatchState& match, const PlayerActionType& _type,
                                           uint8_t _playerind) {
    MatchDto bfr = curr_state;

    PlayerActionDTO action(_type, _playerind);
    match.pushAction(action);

    match.step();
    match.send_results(*this);

    return bfr;
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
