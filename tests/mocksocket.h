#include "common/messenger.h"
#include "gmock/gmock.h"
//#include "common/socket.h"

class MockSocket: public Messenger {
public:
    MOCK_METHOD(int, sendsome, (const void* data, unsigned int sz), (override));
    MOCK_METHOD(unsigned int, recvsome, (void* data, unsigned int sz), (override));

    MOCK_METHOD(unsigned int, trysendall, (const void* data, unsigned int sz), (override));
    MOCK_METHOD(void, sendall, (const void* data, unsigned int sz), (override));

    MOCK_METHOD(unsigned int, tryrecvall, (void* data, unsigned int sz), (override));
    MOCK_METHOD(void, recvall, (void* data, unsigned int sz), (override));

    MOCK_METHOD(int, shutdown, (int how), (override));
    MOCK_METHOD(int, close, (), (override));
};
