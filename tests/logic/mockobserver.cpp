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

const PlayerDTO* MockObserver::getPlayer(int id) const { return curr_state.getPlayer(id); }

void MockObserver::assertPlayerMovedHigher(const PlayerDTO* playerGiven,
                                           const PlayerDTO* playerBase) {
    ASSERT_LT(playerGiven->pos.y, playerBase->pos.y)
            << "New y coord of player is effectivily less than last one, which means higher";
}


void MockObserver::assertPlayerMovedRight(const PlayerDTO* playerGiven,
                                          const PlayerDTO* playerBase) {
    ASSERT_EQ(playerGiven->move_action, TypeMoveAction::MOVE_RIGHT)
            << "Player is currently moving right on ground";
    ASSERT_GT(playerGiven->pos.x, playerBase->pos.x)
            << "New x coord of player is effectivily greater than last one";
}

void MockObserver::assertPlayerMovedAirRight(const PlayerDTO* playerGiven,
                                             const PlayerDTO* playerBase) {
    ASSERT_EQ(playerGiven->move_action, TypeMoveAction::AIR_RIGHT)
            << "Player is currently moving right on air";
    ASSERT_GT(playerGiven->pos.x, playerBase->pos.x)
            << "New x coord of player is effectivily greater than last one";
}


void MockObserver::assertPlayerMovedLeft(const PlayerDTO* playerGiven,
                                         const PlayerDTO* playerBase) {
    ASSERT_EQ(playerGiven->move_action, TypeMoveAction::MOVE_LEFT)
            << "Player is currently moving left on ground";
    ASSERT_LT(playerGiven->pos.x, playerBase->pos.x)
            << "New x coord of player is effectivily less than last one";
}

void MockObserver::assertPlayerMovedAirLeft(const PlayerDTO* playerGiven,
                                            const PlayerDTO* playerBase) {
    ASSERT_EQ(playerGiven->move_action, TypeMoveAction::AIR_LEFT)
            << "Player is currently moving left on air";
    ASSERT_LT(playerGiven->pos.x, playerBase->pos.x)
            << "New x coord of player is effectivily less than last one";
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

std::vector<player_id> MockObserver::getPlayers() const { return std::vector<player_id>(players); }

// Push/notifica eventos a los players, de forma no bloqueante! No tiene precondiciones perse
// Devuelve los players que se desconectaron. Podrian ser notificados directamente
std::vector<player_id> MockObserver::updateState(MatchDto& state) {
    curr_state = state;
    return std::vector<player_id>();
}
