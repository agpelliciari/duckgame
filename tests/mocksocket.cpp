#include "./mocksocket.h"

#include "gmock/gmock.h"
#include "gtest/gtest.h"


// using ::testing::Pointee;
// using ::testing::AllOf;
// using ::testing::AtLeast;
// using ::testing::ThrowsMessage;
// using ::testing::HasSubstr;

using ::testing::Eq;
using ::testing::Ge;
using ::testing::NotNull;
using ::testing::Return;


void MockSocket::expectStrSend(MockSocket* messen, const std::string& msg) {
    uint16_t size = msg.length();
    EXPECT_CALL(*messen, trysendall(NotNull(), Eq(2))).Times(1);
    ON_CALL(*messen, trysendall(NotNull(), Eq(2))).WillByDefault(Return(2));

    EXPECT_CALL(*messen, sendall(Eq(msg.c_str()), Eq(size))).Times(1);
}

void MockSocket::expectStrSendFail(MockSocket* messen, const std::string& msg) {
    uint16_t size = msg.length();
    EXPECT_CALL(*messen, trysendall(NotNull(), Eq(2))).Times(1);
    ON_CALL(*messen, trysendall(NotNull(), Eq(2))).WillByDefault(Return(1));

    EXPECT_CALL(*messen, sendall(Eq(msg.c_str()), Eq(size))).Times(0);
}


void MockSocket::expectClose(MockSocket* messen) {
    EXPECT_CALL(*messen, close()).Times(1);
    EXPECT_CALL(*messen, shutdown(Eq(2))).Times(1);
}
