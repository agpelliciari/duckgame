#include <iostream>

#include "common/clientprotocol.h"
#include "common/core/liberror.h"
#include "common/serverprotocol.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "tests/core/queuesocket.h"
#include "tests/core/testermatchdto.h"

using ::testing::InSequence;
using ::testing::ThrowsMessage;

TEST(TestProtocolMocked, SendReceiveStateNoPlayer) {

    QueueSocket msgbase(20, true);

    MatchDto state;
    

    // Los protocols se encargan. De liberar el shared socket.
    ServerProtocol server(msgbase);
    ClientProtocol client(msgbase);

    server.sendstate(state);
    
    MatchDto state_recv;
    MatchStatsInfo stats_recv;

    // Assert que se mando/se esta jugando.
    ASSERT_TRUE(client.recvstate(stats_recv, state_recv));

    TesterMatchDTO tester(state);
    tester.assertEquals(state);
}


TEST(TestProtocolMocked, SendReceiveState1PlayerMoveLeft) {

    QueueSocket msgbase(20, true);

    MatchDto state;
    PlayerDTO player1(3, true, 10, 5,
                      TypeMoveAction::MOVE_LEFT);  // id, is alive, x , y, move_action
    state.players.push_back(player1);


    // Los protocols se encargan. De liberar el shared socket.
    ServerProtocol server(msgbase);
    ClientProtocol client(msgbase);

    server.sendstate(state);


    MatchDto state_recv;
    MatchStatsInfo stats_recv;

    // Assert que se mando/se esta jugando.
    ASSERT_TRUE(client.recvstate(stats_recv, state_recv));


    TesterMatchDTO tester(state_recv);
    tester.assertEquals(state);
}


TEST(TestProtocolMocked, SendReceiveState2PlayerMoveLeftAndStill) {

    QueueSocket msgbase(20, true);

    MatchDto state;

    PlayerDTO player1(3, true, 10, 5,
                      TypeMoveAction::MOVE_LEFT);  // id, is alive, x , y, move_action
    state.players.push_back(player1);

    PlayerDTO player2(1, false, 1, 0, TypeMoveAction::NONE);  // id, is alive, x , y, move_action
    state.players.push_back(player2);


    // Los protocols se encargan. De liberar el shared socket.
    ServerProtocol server(msgbase);
    ClientProtocol client(msgbase);

    server.sendstate(state);
    
    MatchDto state_recv;
    MatchStatsInfo stats_recv;

    // Assert que se mando/se esta jugando.
    ASSERT_TRUE(client.recvstate(stats_recv, state_recv));

    TesterMatchDTO tester(state_recv);
    tester.assertEquals(state);
}
