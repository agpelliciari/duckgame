#include <iostream>

#include "./mocksocket.h"
#include "common/core/liberror.h"
#include "common/serverprotocol.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"


using ::testing::ThrowsMessage;

TEST(ServerProtocolTest, ServerProtocolClosedSocket) {
    MockSocket* messen = new MockSocket();
    MockSocket::expectClose(messen);

    ServerProtocol protocol(messen);

    protocol.close();
}
