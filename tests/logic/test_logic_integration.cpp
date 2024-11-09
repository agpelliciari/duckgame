#include <iostream>

#include "./mockobserver.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "server/logic_server/match_state.h"


using ::testing::InSequence;
using ::testing::ThrowsMessage;

TEST(IntegrationLogicTest, SendReceiveFirstState3players) {


    MatchDto state(CANCELADA, 2);

    MockObserver observer(state, 3);

    MatchState match;

    match.start_players(observer);

    match.send_results(observer);

    observer.assertHasAllPlayers();
}


TEST(IntegrationLogicTest, SendMoveOnlyPlayer3Right) {
    MatchDto state(CANCELADA, 2);

    MockObserver observer(state, 3);

    MatchState match;

    match.start_players(observer);

    match.send_results(observer);
    observer.assertHasAllPlayers();

    // Cambia el checkpoint.
    state = observer.sendActionAndUpdate(match, MOVE_RIGHT, 3);

    observer.assertPlayerMovedRight(3, state);
}


TEST(IntegrationLogicTest, SendMoveOnlyPlayer3AirRight) {
    MatchDto state(CANCELADA, 2);

    MockObserver observer(state, 3);

    MatchState match;

    match.start_players(observer);

    match.send_results(observer);
    observer.assertHasAllPlayers();

    observer.sendActionAndUpdate(match, MOVE_RIGHT, 3);
    // Cambia el checkpoint.
    state = observer.sendActionAndUpdate(match, JUMP, 3);

    observer.assertPlayerMovedAirRight(3, state);
}
