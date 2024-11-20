#ifndef TESTER_CLIENT
#define TESTER_CLIENT


#include <optional>
#include <string>
#include <vector>

#include "common/clientprotocol.h"
#include "common/core/socket.h"
#include "server/controlreceiver.h"
#include "server/lobbycontainer.h"
class TesterClient {
protected:
    Socket sktclient;
    Socket sktcontrol;


    ClientProtocol client;
    std::optional<ControlReceiver> receiver;

public:
    explicit TesterClient(Socket&& _client, Socket& _serv, LobbyContainer& lobbies);

    uint8_t createClientLobbyDual(const std::vector<std::string>& lobby_maps);
    uint8_t createClientLobbySingle(const std::vector<std::string>& lobby_maps);

    LobbyErrorType assertJoinLobbyFail(uint8_t id_lobby);

    uint8_t assertJoinLobbySingle(uint8_t id_lobby, uint8_t count);
    uint8_t assertJoinLobbyDual(uint8_t id_lobby, uint8_t count, uint8_t* second);


    void assertLobbyStarted(uint8_t count);
    void assertLobbyInfoJoined(uint8_t id);
    void assertLobbyInfoLeft(uint8_t id);
    void assertLobbyHostLeft();
    LobbyErrorType assertLobbyError();


    void startMatch(const std::string& map);
    ClientProtocol& getClient();
    void close();
    void finish();
    bool isReceiverOpen();
    ~TesterClient();
};

#endif
