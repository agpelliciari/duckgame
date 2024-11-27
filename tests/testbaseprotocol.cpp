#include <cstring>
#include <iostream>

//#include "./mocksocket.h"
#include "common/core/liberror.h"
#include "common/core/protocol.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "common/core/simplemessenger.h"

using ::testing::Eq;
using ::testing::ThrowsMessage;

static const char SIMPLE_MSG[] = "UN MENSAJE";


TEST(TestProtocolBase, ProtocolClosedSocket) {
    std::string msg(SIMPLE_MSG);
    SimpleMessenger messen(msg.length(), false);
    Protocol protocol(messen);  // El protocol deberia liberar el queue socket.

    protocol.close();

    // Closed protocol.
    EXPECT_THROW(protocol.sendmsg(msg), std::exception);
}


TEST(TestProtocolBase, ProtocolSendsSimpleMsgString) {
    std::string msg(SIMPLE_MSG);
    SimpleMessenger messen(msg.length(), true);


    Protocol protocol(messen);
    protocol.sendmsg(msg);

    std::string received(protocol.recvmsgstr());

    ASSERT_THAT(received, Eq(msg));
}

TEST(TestProtocolBase, ProtocolSendsSimpleMsgBuffered) {
    int count = strlen(SIMPLE_MSG);
    SimpleMessenger messen(count, true);


    Protocol protocol(messen);
    protocol.sendmsg(SIMPLE_MSG, count);

    std::string received(protocol.recvmsgstr());

    std::string msg(SIMPLE_MSG);
    ASSERT_THAT(received, Eq(msg));
}


TEST(TestProtocolBase, ProtocolRecvsSimpleMsgStringFail) {
    int count = strlen(SIMPLE_MSG);
    SimpleMessenger messen(count - 1, false);
    Protocol protocol(messen);

    EXPECT_THROW(protocol.sendmsg(SIMPLE_MSG, count), LibError);
    EXPECT_THROW(protocol.recvmsgstr(), LibError);
}
