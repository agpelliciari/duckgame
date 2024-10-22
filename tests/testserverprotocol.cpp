#include <iostream>

#include "./mocksocket.h"
#include "common/core/liberror.h"
#include "common/dtos.h"
#include "common/serverprotocol.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"


using ::testing::InSequence;
using ::testing::ThrowsMessage;

TEST(ServerProtocolTest, ServerProtocolClosedSocket) {
    MockSocket* messen = new MockSocket();
    MockSocket::expectClose(messen);

    ServerProtocol protocol(messen);

    protocol.close();
}


TEST(ServerProtocolTest, SendStateSendsMatchInfo) {
    MockSocket* messen = new MockSocket();

    MatchDto match(INICIADA, 1);
    InSequence s;
    MockSocket::expectSendAll(messen, &match.info, sizeof(match.info));
    MockSocket::expectSendByte(messen, 0);

    ServerProtocol protocol(messen);

    protocol.sendstate(match);
}
