#include <iostream>

#include "./mocksocket.h"
#include "client/clientprotocol.h"
//#include "common/messenger.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "server/playerprotocol.h"

using ::testing::AllOf;
using ::testing::AtLeast;
using ::testing::Ge;
using ::testing::HasSubstr;
using ::testing::NotNull;
using ::testing::Pointee;
using ::testing::ThrowsMessage;

TEST(BaseProtocolTest, Check) { EXPECT_EQ(9, (int)(4 + 5)); }

TEST(BaseProtocolTest, MockSocketBase) {
    MockSocket messen;
    EXPECT_CALL(messen, close()).Times(AtLeast(1));


    EXPECT_CALL(messen, sendsome(NotNull(), Ge(10))).Times(AtLeast(1));

    char buff[10];
    messen.sendsome(&buff[0], 10);

    messen.close();
    EXPECT_EQ(10, (int)(4 + 6));
}
