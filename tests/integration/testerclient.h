#ifndef TESTER_CLIENT
#define TESTER_CLIENT


#include "common/clientprotocol.h"
#include "common/core/socket.h"
#include "server/controlreceiver.h"
#include "server/lobbycontainer.h"

class TesterClient {
protected:
    Socket sktclient;
    Socket sktcontrol;


    ClientProtocol client;
    ControlReceiver receiver;

public:
    explicit TesterClient(Socket&& _client, Socket& _serv, LobbyContainer& lobbies);

    uint8_t createClientLobbyDual();
    uint8_t createClientLobbySingle();

    uint8_t assertJoinLobbySingle(uint8_t id_lobby, uint8_t count);
    uint8_t assertJoinLobbyDual(uint8_t id_lobby, uint8_t count, uint8_t* second);


    void assertLobbyStarted(uint8_t count);
    void assertLobbyJoinNotif(uint8_t id);
    void assertLobbyLeaveNotif(uint8_t id);


    void startMatch();
    ClientProtocol& getClient();
    void close();
};

#endif
