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
using ::testing::MatcherCast;
using ::testing::Pointee;
using ::testing::WhenDynamicCastTo;

using ::testing::NotNull;
using ::testing::Return;

#define VoidPoint(type, data) MatcherCast<void*>(MatcherCast<type*>(Pointee(Eq(data))))
#define ConstVoidPoint(type, data) \
    MatcherCast<const void*>(MatcherCast<const type*>(Pointee(Eq(data))))

void MockSocket::expectSendByte(MockSocket* messen, const uint8_t byte) {
    EXPECT_CALL(*messen, sendsome(ConstVoidPoint(uint8_t, byte), Eq(1))).Times(1);
    ON_CALL(*messen, sendsome(ConstVoidPoint(uint8_t, byte), Eq(1))).WillByDefault(Return(1));
}

void MockSocket::expectSendByteFail(MockSocket* messen, const uint8_t byte) {
    EXPECT_CALL(*messen, sendsome(ConstVoidPoint(uint8_t, byte), Eq(1))).Times(1);
    ON_CALL(*messen, sendsome(ConstVoidPoint(uint8_t, byte), Eq(1))).WillByDefault(Return(0));
}


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


void MockSocket::expectSendAll(MockSocket* messen, const void* data, const int count) {
    EXPECT_CALL(*messen, sendall(Eq(data), Eq(count))).Times(1);
}

void MockSocket::expectRecvAll(MockSocket* messen, const void* data, const int count) {
    EXPECT_CALL(*messen, recvall(Eq(data), Eq(count))).Times(1);
}

void MockSocket::expectTryRecvAll(MockSocket* messen, const void* data, const int count) {
    EXPECT_CALL(*messen, tryrecvall(Eq(data), Eq(count))).Times(1);
    ON_CALL(*messen, tryrecvall(Eq(data), Eq(count))).WillByDefault(Return(count));
}

void MockSocket::expectTryRecvFail(MockSocket* messen, const void* data, const int count) {
    EXPECT_CALL(*messen, tryrecvall(Eq(data), Eq(count))).Times(1);
    ON_CALL(*messen, tryrecvall(Eq(data), Eq(count))).WillByDefault(Return(count - 1));
}


void MockSocket::expectClose(MockSocket* messen) {
    EXPECT_CALL(*messen, close()).Times(1);
    EXPECT_CALL(*messen, shutdown(Eq(2))).Times(1);
}


struct some_data getSomeData(uint8_t sub1, uint8_t sub2, SomeType type1, SomeType type2) {
    struct some_data res;

    res.sub1.subnum = sub1;
    res.sub1.tipo = type1;
    res.sub2.subnum = sub2;
    res.sub2.tipo = type2;

    res.primerid = 0;
    res.segundoid = 0;
    return res;
}
