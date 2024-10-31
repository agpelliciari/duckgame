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
