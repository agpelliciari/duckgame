#include <iostream>

#include "./queuesocket.h"
#include "common/core/liberror.h"
#include "common/dtos.h"
#include "common/serverprotocol.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"


/*
using ::testing::InSequence;
using ::testing::ThrowsMessage;

TEST(ServerProtocolTest, ServerProtocolClosedSocket) {
    MockSocket* messen = new MockSocket();
    MockSocket::expectClose(messen);

    ServerProtocol protocol(messen);

    protocol.close();
}


TEST(ServerProtocolTest, SendStateSendsMatchInfoNoPlayers) {
    MockSocket* messen = new MockSocket();

    MatchDto match(INICIADA, 1);
    InSequence s;
    MockSocket::expectSendAll(messen, &match.info, sizeof(match.info));
    MockSocket::expectSendByte(messen, 0);

    ServerProtocol protocol(messen);

    protocol.sendstate(match);
}

TEST(ServerProtocolTest, SendStateSendsMatchInfoFail) {
    MockSocket* messen = new MockSocket();

    MatchDto match(INICIADA, 4);
    // match.players.push_back(PlayerDTO());

    MockSocket::expectSendAll(messen, &(match.info), sizeof(match.info));
    MockSocket::expectSendByteFail(messen, 0);

    ServerProtocol protocol(messen);
    EXPECT_THROW(protocol.sendstate(match), LibError);
}

*/
