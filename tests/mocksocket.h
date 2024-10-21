#ifndef MOCK_SOCKET
#define MOCK_SOCKET

#include <cstdint>
#include <string>

#include "common/core/messenger.h"
#include "gmock/gmock.h"

enum SomeType : unsigned int {
    SOME1 = 1,
    SOME2 = 2,
    SOME32 = 0x20,
};

struct some_sub_data {
    SomeType tipo;   // cppcheck-suppress unusedStructMember
    uint8_t subnum;  // cppcheck-suppress unusedStructMember
} __attribute__((packed));

struct some_data {
    uint8_t primerid;           // cppcheck-suppress unusedStructMember
    struct some_sub_data sub1;  // cppcheck-suppress unusedStructMember
    uint8_t segundoid;          // cppcheck-suppress unusedStructMember
    struct some_sub_data sub2;  // cppcheck-suppress unusedStructMember
};

struct some_data getSomeData(uint8_t sub1, uint8_t sub2, SomeType type1, SomeType type2);

class MockSocket: public Messenger {
public:
    static void expectStrSend(MockSocket* messen, const std::string& msg);
    static void expectStrSendFail(MockSocket* messen, const std::string& msg);
    static void expectClose(MockSocket* messen);

    static void expectSendAll(MockSocket* messen, const void* data, const int count);
    static void expectRecvAll(MockSocket* messen, const void* data, const int count);
    static void expectTryRecvAll(MockSocket* messen, const void* data, const int count);
    static void expectTryRecvFail(MockSocket* messen, const void* data, const int count);

    MOCK_METHOD(int, sendsome, (const void* data, unsigned int sz), (override));
    MOCK_METHOD(unsigned int, recvsome, (void* data, unsigned int sz), (override));

    MOCK_METHOD(unsigned int, trysendall, (const void* data, unsigned int sz), (override));
    MOCK_METHOD(void, sendall, (const void* data, unsigned int sz), (override));

    MOCK_METHOD(unsigned int, tryrecvall, (void* data, unsigned int sz), (override));
    MOCK_METHOD(void, recvall, (void* data, unsigned int sz), (override));

    MOCK_METHOD(int, shutdown, (int how), (override));
    MOCK_METHOD(int, close, (), (override));
};

#endif
