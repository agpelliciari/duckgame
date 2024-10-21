#include <cstring>
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


TEST(BaseProtocolTest, ProtocolSendsBytesSimple) {
    MockSocket* messen = new MockSocket();
    int count = strlen(SIMPLE_MSG);
    MockSocket::expectSendAll(messen, SIMPLE_MSG, count);

    Protocol protocol(messen);
    protocol.sendbytes(SIMPLE_MSG, count);
}

TEST(BaseProtocolTest, ProtocolSendsBytesStruct) {
    MockSocket* messen = new MockSocket();

    struct some_data data = getSomeData(12, 32, SOME1, SOME32);
    data.primerid = 23;

    MockSocket::expectSendAll(messen, &data, sizeof(data));

    Protocol protocol(messen);
    protocol.sendbytes(&data, sizeof(data));
}


TEST(BaseProtocolTest, ProtocolRecvsBytesStruct) {
    MockSocket* messen = new MockSocket();

    struct some_data data = getSomeData(12, 32, SOME1, SOME32);
    data.primerid = 23;

    MockSocket::expectTryRecvAll(messen, &data, sizeof(data));

    Protocol protocol(messen);

    bool done = protocol.tryrecvbytes(&data, sizeof(data));

    EXPECT_TRUE(done) << "Se esperaba que se notifique recibio el struct";
}
