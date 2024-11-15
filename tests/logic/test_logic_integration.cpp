#include <iostream>

#include "./mockobserver.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "server/logic_server/match_state.h"


using ::testing::InSequence;
using ::testing::ThrowsMessage;

TEST(TestLogicIntegration, SendReceiveFirstState3players) {


    MatchDto state;

    MockObserver observer(state, 3);

    MatchState match;

    match.start_players(observer);

    match.send_results(observer);

    observer.assertHasAllPlayers();
}


TEST(TestLogicIntegration, SendMoveOnlyPlayer3Right) {
    MatchDto state;

    MockObserver observer(state, 3);

    MatchState match;

    match.start_players(observer);

    match.send_results(observer);
    observer.assertHasAllPlayers();

    // Cambia el checkpoint.
    int idPlayer = 3;

    state = observer.sendActionAndUpdate(match, MOVE_RIGHT, idPlayer);

    const PlayerDTO* playerGiven = observer.getPlayer(idPlayer);
    ASSERT_TRUE(playerGiven != NULL)
            << "El player de id " << idPlayer << "estaba contenido en el curr state";

    const PlayerDTO* playerBase = state.getPlayer(idPlayer);

    observer.assertPlayerMovedRight(playerGiven, playerBase);
}

TEST(TestLogicIntegration, SendMoveOnlyPlayer3Left) {
    MatchDto state;

    MockObserver observer(state, 3);

    MatchState match;

    match.start_players(observer);

    match.send_results(observer);
    observer.assertHasAllPlayers();

    // Cambia el checkpoint.
    int idPlayer = 3;

    state = observer.sendActionAndUpdate(match, MOVE_LEFT, idPlayer);

    const PlayerDTO* playerGiven = observer.getPlayer(idPlayer);
    ASSERT_TRUE(playerGiven != NULL)
            << "El player de id " << idPlayer << "estaba contenido en el curr state";

    const PlayerDTO* playerBase = state.getPlayer(idPlayer);

    observer.assertPlayerMovedLeft(playerGiven, playerBase);
}


TEST(TestLogicIntegration, SendMoveOnlyPlayer3AirRight) {
    MatchDto state;

    MockObserver observer(state, 3);

    MatchState match;

    match.start_players(observer);

    match.send_results(observer);
    observer.assertHasAllPlayers();

    int idPlayer = 3;

    observer.sendActionAndUpdate(match, MOVE_RIGHT, idPlayer);
    // Cambia el checkpoint.
    state = observer.sendActionAndUpdate(match, JUMP, idPlayer);

    const PlayerDTO* playerGiven = observer.getPlayer(idPlayer);
    ASSERT_TRUE(playerGiven != NULL)
            << "El player de id " << idPlayer << "estaba contenido en el curr state";


    const PlayerDTO* playerBase = state.getPlayer(idPlayer);

    observer.assertPlayerMovedHigher(playerGiven, playerBase);
    observer.assertPlayerMovedAirRight(playerGiven, playerBase);
}


TEST(TestLogicIntegration, SendMoveOnlyPlayer3AirLeft) {
    MatchDto state;

    MockObserver observer(state, 3);

    MatchState match;

    match.start_players(observer);

    match.send_results(observer);
    observer.assertHasAllPlayers();

    int idPlayer = 3;

    observer.sendActionAndUpdate(match, MOVE_LEFT, idPlayer);
    // Cambia el checkpoint.
    state = observer.sendActionAndUpdate(match, JUMP, idPlayer);

    const PlayerDTO* playerGiven = observer.getPlayer(idPlayer);
    ASSERT_TRUE(playerGiven != NULL)
            << "El player de id " << idPlayer << "estaba contenido en el curr state";


    const PlayerDTO* playerBase = state.getPlayer(idPlayer);

    observer.assertPlayerMovedHigher(playerGiven, playerBase);
    observer.assertPlayerMovedAirLeft(playerGiven, playerBase);
}


TEST(TestLogicIntegration, SendMoveOnlyPlayer3Jumps) {
    MatchDto state;

    MockObserver observer(state, 3);

    MatchState match;

    match.start_players(observer);

    match.send_results(observer);
    observer.assertHasAllPlayers();

    int idPlayer = 3;

    state = observer.sendActionAndUpdate(match, MOVE_LEFT, idPlayer);
    // Cambia el checkpoint.
    observer.sendActionAndUpdate(match, JUMP, idPlayer);

    const PlayerDTO* playerGiven = observer.getPlayer(idPlayer);
    ASSERT_TRUE(playerGiven != NULL)
            << "El player de id " << idPlayer << "estaba contenido en el curr state";


    const PlayerDTO* playerBase = state.getPlayer(idPlayer);

    observer.assertPlayerMovedHigher(playerGiven, playerBase);
}
