#include <iostream>

#include "./mocksocket.h"
#include "common/core/liberror.h"
#include "common/core/protocol.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

using ::testing::ThrowsMessage;

static const char SIMPLE_MSG[] = "UN MENSAJE";


TEST(BaseProtocolTest, ProtocolClosedSocket) {
    MockSocket* messen = new MockSocket();
    MockSocket::expectClose(messen);

    Protocol protocol(messen);

    protocol.close();
}


TEST(BaseProtocolTest, ProtocolSendsSimpleMsgString) {
    MockSocket* messen = new MockSocket();
    std::string msg(SIMPLE_MSG);
    MockSocket::expectStrSend(messen, msg);

    Protocol protocol(messen);
    protocol.sendmsg(msg);
}


TEST(BaseProtocolTest, ProtocolSendsSimpleMsgStringFail) {
    MockSocket* messen = new MockSocket();
    std::string msg(SIMPLE_MSG);
    MockSocket::expectStrSendFail(messen, msg);

    Protocol protocol(messen);
    EXPECT_THROW(protocol.sendmsg(msg), LibError);
}
