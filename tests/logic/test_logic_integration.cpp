#include <iostream>

#include "./mockobserver.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "server/logic_server/match_state.h"
#include "common/dtosmap.h"


using ::testing::InSequence;
using ::testing::ThrowsMessage;

#define WIDTH 20
#define HEIGHT 20
static void buildMapSimple(struct ObjectsInfo& info){
    for(int x = 0; x < info.map_width;x++){
        info.blocks.emplace_back(x, 0); // x, y.
    }
    
    for(int x = 0; x < 20;x++){
        info.blocks.emplace_back(x, 10); // x, y.
    }

    info.player_spawns.emplace_back(1,1);
    info.player_spawns.emplace_back(1,11);
    info.player_spawns.emplace_back(19,1);
    info.player_spawns.emplace_back(19,11);
    
}

TEST(IntegrationLogicTest, SendReceiveFirstState3players) {
    struct ObjectsInfo objs(WIDTH,HEIGHT);
    buildMapSimple(objs);
    
    MatchDto state;
    MatchStatsInfo stats;
    
    

    MockObserver observer(state, 3);

    MatchState match;
    
    match.add_objects(objs);
    match.start_players(observer,stats);

    match.send_results(observer);

    observer.assertHasAllPlayers();
}


TEST(IntegrationLogicTest, SendMoveOnlyPlayer3Right) {
    struct ObjectsInfo objs(WIDTH,HEIGHT);
    buildMapSimple(objs);
    
    MatchDto state;
    MatchStatsInfo stats;

    MockObserver observer(state, 3);

    MatchState match;

    match.add_objects(objs);
    match.start_players(observer,stats);

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

TEST(IntegrationLogicTest, SendMoveOnlyPlayer3Left) {
    struct ObjectsInfo objs(WIDTH,HEIGHT);
    buildMapSimple(objs);
    
    MatchDto state;
    MatchStatsInfo stats;

    MockObserver observer(state, 3);

    MatchState match;

    match.add_objects(objs);
    match.start_players(observer,stats);

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


TEST(IntegrationLogicTest, SendMoveOnlyPlayer3AirRight) {
    struct ObjectsInfo objs(WIDTH,HEIGHT);
    buildMapSimple(objs);

    MatchDto state;
    MatchStatsInfo stats;

    MockObserver observer(state, 3);

    MatchState match;

    match.add_objects(objs);
    match.start_players(observer,stats);

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


TEST(IntegrationLogicTest, SendMoveOnlyPlayer3AirLeft) {
    struct ObjectsInfo objs(WIDTH,HEIGHT);
    buildMapSimple(objs);
    
    MatchDto state;
    MatchStatsInfo stats;

    MockObserver observer(state, 3);

    MatchState match;

    match.add_objects(objs);
    match.start_players(observer,stats);

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


TEST(IntegrationLogicTest, SendMoveOnlyPlayer3Jumps) {
    struct ObjectsInfo objs(WIDTH,HEIGHT);
    buildMapSimple(objs);
    
    MatchDto state;
    MatchStatsInfo stats;

    MockObserver observer(state, 3);

    MatchState match;
    
    match.add_objects(objs);
    match.start_players(observer,stats);

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
