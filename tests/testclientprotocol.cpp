#include <iostream>

#include "./mocksocket.h"
#include "common/clientprotocol.h"
#include "common/core/liberror.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"


using ::testing::AllOf;
using ::testing::AtLeast;
using ::testing::Eq;
using ::testing::Ge;
using ::testing::HasSubstr;
using ::testing::NotNull;
using ::testing::Pointee;
using ::testing::Return;
using ::testing::ThrowsMessage;

//#include <arpa/inet.h>

static void expectClose(MockSocket* messen) {
    EXPECT_CALL(*messen, close()).Times(1);
    EXPECT_CALL(*messen, shutdown(Eq(2))).Times(1);
}

TEST(ClientProtocolTest, ClientProtocolClosedSocket) {
    MockSocket* messen = new MockSocket();
    expectClose(messen);

    Protocol protocol(messen);

    protocol.close();
}
