#include <string>

#include "common/core/messenger.h"
#include "gmock/gmock.h"

class MockSocket: public Messenger {
public:
    static void expectStrSend(MockSocket* messen, const std::string& msg);
    static void expectStrSendFail(MockSocket* messen, const std::string& msg);
    static void expectClose(MockSocket* messen);

    MOCK_METHOD(int, sendsome, (const void* data, unsigned int sz), (override));
    MOCK_METHOD(unsigned int, recvsome, (void* data, unsigned int sz), (override));

    MOCK_METHOD(unsigned int, trysendall, (const void* data, unsigned int sz), (override));
    MOCK_METHOD(void, sendall, (const void* data, unsigned int sz), (override));

    MOCK_METHOD(unsigned int, tryrecvall, (void* data, unsigned int sz), (override));
    MOCK_METHOD(void, recvall, (void* data, unsigned int sz), (override));

    MOCK_METHOD(int, shutdown, (int how), (override));
    MOCK_METHOD(int, close, (), (override));
};
