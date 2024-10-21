#include <iostream>

#include "./mocksocket.h"
#include "common/clientprotocol.h"
#include "common/core/liberror.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

using ::testing::ThrowsMessage;

TEST(ClientProtocolTest, ClientProtocolClosedSocket) {
    MockSocket* messen = new MockSocket();
    MockSocket::expectClose(messen);

    ClientProtocol protocol(messen);

    protocol.close();
}
