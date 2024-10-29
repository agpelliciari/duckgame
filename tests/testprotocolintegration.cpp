#include <iostream>

#include "./queuesocket.h"
#include "./sharedsocket.h"
#include "common/clientprotocol.h"
#include "common/core/liberror.h"
#include "common/dtos.h"
#include "common/serverprotocol.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"


using ::testing::InSequence;
using ::testing::ThrowsMessage;

static void assertPlayerAreEq(const PlayerDTO& expected, const PlayerDTO& given) {

    ASSERT_EQ(given.id, expected.id) << "Players id are the same";
    ASSERT_EQ(given.coord_x, expected.coord_x) << "Players x are the same";
    ASSERT_EQ(given.coord_y, expected.coord_y) << "Players y are the same";
    ASSERT_EQ(given.weapon, expected.weapon) << "Players weapon are the same";
    ASSERT_EQ(given.move_action, expected.move_action) << "Players move_action are the same";
    ASSERT_EQ(given.doing_action, expected.doing_action) << "Players doing_action are the same";
    ASSERT_EQ(given.is_alive, expected.is_alive) << "Players is alive are the same";
    ASSERT_EQ(given.helmet, expected.helmet) << "Players helmet are the same";
    ASSERT_EQ(given.chest_armor, expected.chest_armor) << "Players chest armor are the same";
    ASSERT_EQ(given.aiming_up, expected.aiming_up) << "Players aiming up are the same";
}
static void assertMatchDtoEq(const MatchDto& expected, const MatchDto& given) {
    ASSERT_EQ(given.info.estado, expected.info.estado) << "State is the same";
    ASSERT_EQ(given.info.numronda, expected.info.numronda) << "State round number are the same";

    ASSERT_EQ(given.players.size(), expected.players.size()) << "Player counts are the same";

    auto givenPlayer = given.players.begin();
    int ind = 0;
    for (auto expPlayer = expected.players.begin(); expPlayer != expected.players.end();) {
        ind++;
        PlayerDTO playerExpected = *expPlayer;
        PlayerDTO playerGiven = *givenPlayer;

        assertPlayerAreEq(playerGiven, playerExpected);

        ++expPlayer;
        ++givenPlayer;
    }
}

TEST(IntegrationProtocolTest, SendReceiveStateNoPlayer) {

    QueueSocket msgbase(20, true);

    MatchDto state(INICIADA, 2);

    // Los protocols se encargan. De liberar el shared socket.
    ServerProtocol server(new SharedSocket(msgbase));
    ClientProtocol client(new SharedSocket(msgbase));

    server.sendstate(state);

    MatchDto result = client.recvstate();

    assertMatchDtoEq(state, result);
}


TEST(IntegrationProtocolTest, SendReceiveState1PlayerMoveLeft) {

    QueueSocket msgbase(20, true);

    MatchDto state(INICIADA, 2);
    PlayerDTO player1;
    player1.id = 3;
    player1.coord_x = 10;
    player1.coord_y = 5;
    player1.move_action = TypeMoveAction::MOVE_LEFT;

    state.players.push_back(player1);


    // Los protocols se encargan. De liberar el shared socket.
    ServerProtocol server(new SharedSocket(msgbase));
    ClientProtocol client(new SharedSocket(msgbase));

    server.sendstate(state);

    MatchDto result = client.recvstate();

    assertMatchDtoEq(state, result);
}


TEST(IntegrationProtocolTest, SendReceiveState2PlayerMoveLeftAndStill) {

    QueueSocket msgbase(20, true);

    MatchDto state(INICIADA, 2);
    PlayerDTO player1;
    player1.id = 3;
    player1.coord_x = 10;
    player1.coord_y = 5;
    player1.move_action = TypeMoveAction::MOVE_LEFT;

    state.players.push_back(player1);
    PlayerDTO player2;
    player2.id = 1;
    player2.coord_x = 1;
    player2.coord_y = 0;
    player2.move_action = TypeMoveAction::NONE;
    state.players.push_back(player2);


    // Los protocols se encargan. De liberar el shared socket.
    ServerProtocol server(new SharedSocket(msgbase));
    ClientProtocol client(new SharedSocket(msgbase));

    server.sendstate(state);

    MatchDto result = client.recvstate();

    assertMatchDtoEq(state, result);
}
