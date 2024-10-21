#include <iostream>

#include "./mocksocket.h"
#include "common/core/liberror.h"
#include "common/core/protocol.h"
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

static const char SIMPLE_MSG[] = "UN MENSAJE";

static void expectStrSend(MockSocket* messen, const std::string& msg) {
    uint16_t size = msg.length();
    EXPECT_CALL(*messen, trysendall(NotNull(), Eq(2))).Times(1);
    ON_CALL(*messen, trysendall(NotNull(), Eq(2))).WillByDefault(Return(2));

    EXPECT_CALL(*messen, sendall(Eq(msg.c_str()), Eq(size))).Times(1);
}

static void expectStrSendFail(MockSocket* messen, const std::string& msg) {
    uint16_t size = msg.length();
    EXPECT_CALL(*messen, trysendall(NotNull(), Eq(2))).Times(1);
    ON_CALL(*messen, trysendall(NotNull(), Eq(2))).WillByDefault(Return(1));

    EXPECT_CALL(*messen, sendall(Eq(msg.c_str()), Eq(size))).Times(0);
}


static void expectClose(MockSocket* messen) {
    EXPECT_CALL(*messen, close()).Times(1);
    EXPECT_CALL(*messen, shutdown(Eq(2))).Times(1);
}

TEST(BaseProtocolTest, ProtocolClosedSocket) {
    MockSocket* messen = new MockSocket();
    expectClose(messen);

    Protocol protocol(messen);

    protocol.close();
}


TEST(BaseProtocolTest, ProtocolSendsSimpleMsgString) {
    MockSocket* messen = new MockSocket();
    std::string msg(SIMPLE_MSG);
    expectStrSend(messen, msg);

    Protocol protocol(messen);
    protocol.sendmsg(msg);
}


TEST(BaseProtocolTest, ProtocolSendsSimpleMsgStringFail) {
    MockSocket* messen = new MockSocket();
    std::string msg(SIMPLE_MSG);
    expectStrSendFail(messen, msg);

    Protocol protocol(messen);
    EXPECT_THROW(protocol.sendmsg(msg), LibError);
}
