#include "gmock/gmock.h"
//#include "common/messenger.h"
#include "common/socket.h"

class Messenger2 {
public:
    virtual int close() = 0;
    virtual ~Messenger2() {}
};
class MockSocket: public Messenger2 {
public:
    // MOCK_METHOD(int, sendsome, (const void* data, unsigned int sz), (override));
    // MOCK_METHOD(unsigned int, recvsome, (void* data, unsigned int sz), (override));

    // MOCK_METHOD(unsigned int, trysendall, (const void* data, unsigned int sz), (override));
    // MOCK_METHOD(void, sendall, (const void* data, unsigned int sz), (override));

    // MOCK_METHOD(unsigned int, tryrecvall, (void* data, unsigned int sz), (override));
    // MOCK_METHOD(void, recvall, (void* data, unsigned int sz), (override));

    // MOCK_METHOD(int, shutdown, (int how), (override));
    MOCK_METHOD(int, close, (), (override));
};
