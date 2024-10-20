#include <iostream>

#include "./mocksocket.h"
#include "client/clientprotocol.h"
//#include "common/messenger.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "server/playerprotocol.h"

using ::testing::AllOf;
using ::testing::AtLeast;
using ::testing::HasSubstr;
using ::testing::ThrowsMessage;

TEST(BaseProtocolTest, Check) { EXPECT_EQ(9, (int)(4 + 5)); }

TEST(BaseProtocolTest, MockSocketBase) {
    MockSocket messen;
    EXPECT_CALL(messen, close()).Times(AtLeast(1));
    messen.close();

    EXPECT_EQ(11, (int)(4 + 6));
}
