#include <cstring>
#include <iostream>

//#include "./mocksocket.h"
#include "common/core/liberror.h"
#include "common/core/protocol.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "tests/core/queuesocket.h"

using ::testing::Eq;
using ::testing::ThrowsMessage;

static const char SIMPLE_MSG[] = "UN MENSAJE";


TEST(BaseProtocolTest, ProtocolClosedSocket) {
    std::string msg(SIMPLE_MSG);
    QueueSocket messen(msg.length(), false);
    Protocol protocol(messen);  // El protocol deberia liberar el queue socket.

    protocol.close();

    // Closed protocol.
    EXPECT_THROW(protocol.sendmsg(msg), std::exception);
}


TEST(BaseProtocolTest, ProtocolSendsSimpleMsgString) {
    std::string msg(SIMPLE_MSG);
    QueueSocket messen(msg.length(), true);


    Protocol protocol(messen);
    protocol.sendmsg(msg);

    std::string received(protocol.recvmsgstr());

    ASSERT_THAT(received, Eq(msg));
}

TEST(BaseProtocolTest, ProtocolSendsSimpleMsgBuffered) {
    int count = strlen(SIMPLE_MSG);
    QueueSocket messen(count, true);


    Protocol protocol(messen);
    protocol.sendmsg(SIMPLE_MSG, count);

    std::string received(protocol.recvmsgstr());

    std::string msg(SIMPLE_MSG);
    ASSERT_THAT(received, Eq(msg));
}


TEST(BaseProtocolTest, ProtocolRecvsSimpleMsgStringFail) {
    int count = strlen(SIMPLE_MSG);
    QueueSocket messen(count - 1, false);
    Protocol protocol(messen);

    EXPECT_THROW(protocol.sendmsg(SIMPLE_MSG, count), LibError);
    EXPECT_THROW(protocol.recvmsgstr(), LibError);
}
