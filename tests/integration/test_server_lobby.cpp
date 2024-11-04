#include <iostream>

#include "./testerclient.h"
#include "common/core/liberror.h"
#include "common/dtos.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "server/lobbycontainer.h"

using ::testing::InSequence;
using ::testing::ThrowsMessage;

class ServerIntegrationTest: public ::testing::Test {
protected:
    Socket sktserver;
    LobbyContainer lobbies;

    inline ServerIntegrationTest(): sktserver("2048"), lobbies() {}

    Socket openClient() { return Socket(NULL, "2048"); }

    virtual ~ServerIntegrationTest() {
        sktserver.shutdown(2);
        sktserver.close();
    }
};


TEST_F(ServerIntegrationTest, SimpleCreateLobbyDual) {

    TesterClient host(openClient(), sktserver, lobbies);

    uint8_t id_lobby = host.createClientLobbyDual();
    ASSERT_EQ(id_lobby, 1) << "ID lobby received by client is 1, since its the first match";
    ASSERT_EQ(lobbies.countMatches(), 1) << "Lobby was created";

    host.startMatch();

    // 2 is count of players.
    host.assertLobbyStarted(2);
}

TEST_F(ServerIntegrationTest, SimpleCreateLobbyDualInmediateDisconnect) {

    TesterClient host(openClient(), sktserver, lobbies);

    uint8_t id_lobby = host.createClientLobbyDual();
    ASSERT_EQ(id_lobby, 1) << "ID lobby received by client is 1, since its the first match";
    ASSERT_EQ(lobbies.countMatches(), 1) << "Lobby was created";

    host.startMatch();
    host.close();
}


TEST_F(ServerIntegrationTest, SimpleCreateLobbySingle) {

    TesterClient host(openClient(), sktserver, lobbies);

    uint8_t id_lobby = host.createClientLobbySingle();
    ASSERT_EQ(id_lobby, 1) << "ID lobby received by client is 1, since its the first match";
    host.startMatch();

    // 1 is count of players. Should not start maybe?
    host.assertLobbyStarted(1);
}


TEST_F(ServerIntegrationTest, SimpleCreateLobbyAndJoin) {
    TesterClient host(openClient(), sktserver, lobbies);

    uint8_t id_lobby = host.createClientLobbySingle();
    ASSERT_EQ(id_lobby, 1) << "ID lobby received by client is 1, since its the first match";


    TesterClient joined1(openClient(), sktserver, lobbies);

    uint8_t first = 0;
    uint8_t second = joined1.assertJoinLobbyDual(id_lobby, 1, &first);

    ASSERT_EQ(first, 2) << "ID joined first is correct";
    ASSERT_EQ(second, 3) << "ID joined second is correct";

    host.assertLobbyInfoJoined(first);
    host.assertLobbyInfoJoined(second);

    host.startMatch();

    // 1 is count of players. Should not start maybe?
    host.assertLobbyStarted(3);
    joined1.assertLobbyStarted(3);
}

TEST_F(ServerIntegrationTest, JoinFailedNotFound) {
    TesterClient joined1(openClient(), sktserver, lobbies);

    LobbyErrorType error = joined1.assertJoinLobbyFail(23);

    ASSERT_EQ(error, LOBBY_NOT_FOUND) << "Error type was lobby not found";
}


TEST_F(ServerIntegrationTest, SimpleCreateLobbyAndJoinSingle) {
    TesterClient host(openClient(), sktserver, lobbies);

    uint8_t id_lobby = host.createClientLobbySingle();
    ASSERT_EQ(id_lobby, 1) << "ID lobby received by client is 1, since its the first match";


    TesterClient joined1(openClient(), sktserver, lobbies);

    uint8_t first = joined1.assertJoinLobbySingle(id_lobby, 1);
    ASSERT_EQ(first, 2) << "ID joined first is correct";

    host.assertLobbyInfoJoined(first);

    host.startMatch();

    // 1 is count of players. Should not start maybe?
    host.assertLobbyStarted(2);
    joined1.assertLobbyStarted(2);
}


TEST_F(ServerIntegrationTest, SimpleCreateLobbyAndJoinButLeft) {
    TesterClient host(openClient(), sktserver, lobbies);

    uint8_t id_lobby = host.createClientLobbyDual();
    ASSERT_EQ(id_lobby, 1) << "ID lobby received by client is 1, since its the first match";


    TesterClient joined1(openClient(), sktserver, lobbies);

    uint8_t first = 0;
    uint8_t second = joined1.assertJoinLobbyDual(id_lobby, 2, &first);

    ASSERT_EQ(first, 3) << "ID joined first is correct";
    ASSERT_EQ(second, 4) << "ID joined second is correct";

    host.assertLobbyInfoJoined(first);
    host.assertLobbyInfoJoined(second);

    joined1.close();
    host.assertLobbyInfoLeft(first);
    host.assertLobbyInfoLeft(second);

    host.startMatch();

    host.assertLobbyStarted(2);
}


TEST_F(ServerIntegrationTest, SimpleJoinMultiple) {
    TesterClient host(openClient(), sktserver, lobbies);

    uint8_t id_lobby = host.createClientLobbyDual();
    ASSERT_EQ(id_lobby, 1) << "ID lobby received by client is 1, since its the first match";


    TesterClient joined1(openClient(), sktserver, lobbies);
    TesterClient joined2(openClient(), sktserver, lobbies);

    uint8_t first = joined1.assertJoinLobbySingle(id_lobby, 2);
    uint8_t second = joined2.assertJoinLobbySingle(id_lobby, 3);
    ASSERT_EQ(first, 3) << "ID joined first is correct";
    ASSERT_EQ(second, 4) << "ID joined second is correct";


    host.assertLobbyInfoJoined(first);

    host.assertLobbyInfoJoined(second);
    joined1.assertLobbyInfoJoined(second);

    host.startMatch();

    host.assertLobbyStarted(4);
    joined1.assertLobbyStarted(4);
    joined2.assertLobbyStarted(4);
}


TEST_F(ServerIntegrationTest, SimpleJoinMultipleWithLeaves) {
    TesterClient host(openClient(), sktserver, lobbies);

    uint8_t id_lobby = host.createClientLobbyDual();
    ASSERT_EQ(id_lobby, 1) << "ID lobby received by client is 1, since its the first match";


    TesterClient joined1(openClient(), sktserver, lobbies);
    TesterClient joined2(openClient(), sktserver, lobbies);

    uint8_t first = joined1.assertJoinLobbySingle(id_lobby, 2);
    uint8_t second = joined2.assertJoinLobbySingle(id_lobby, 3);
    ASSERT_EQ(first, 3) << "ID joined first is correct";
    ASSERT_EQ(second, 4) << "ID joined second is correct";


    host.assertLobbyInfoJoined(first);

    host.assertLobbyInfoJoined(second);
    joined1.assertLobbyInfoJoined(second);

    joined1.close();

    host.assertLobbyInfoLeft(first);
    joined2.assertLobbyInfoLeft(first);

    TesterClient joined3(openClient(), sktserver, lobbies);

    uint8_t fourth = joined3.assertJoinLobbySingle(id_lobby, 3);
    ASSERT_EQ(fourth, 5) << "ID joined fifth is correct";

    host.assertLobbyInfoJoined(fourth);
    joined2.assertLobbyInfoJoined(fourth);

    host.startMatch();

    host.assertLobbyStarted(4);
    joined2.assertLobbyStarted(4);
    joined3.assertLobbyStarted(4);
}


TEST_F(ServerIntegrationTest, SimpleJoinMultipleCancel) {
    TesterClient host(openClient(), sktserver, lobbies);

    uint8_t id_lobby = host.createClientLobbyDual();
    ASSERT_EQ(id_lobby, 1) << "ID lobby received by client is 1, since its the first match";


    TesterClient joined1(openClient(), sktserver, lobbies);
    TesterClient joined2(openClient(), sktserver, lobbies);

    uint8_t first = joined1.assertJoinLobbySingle(id_lobby, 2);
    uint8_t second = joined2.assertJoinLobbySingle(id_lobby, 3);
    ASSERT_EQ(first, 3) << "ID joined first is correct";
    ASSERT_EQ(second, 4) << "ID joined second is correct";


    host.assertLobbyInfoJoined(first);

    host.assertLobbyInfoJoined(second);
    joined1.assertLobbyInfoJoined(second);

    host.finish();

    joined1.assertLobbyCanceled();
    joined2.assertLobbyCanceled();

    joined1.finish();
    joined2.finish();  // Para garantizar sincronismo. Antes de verificar el delete.

    ASSERT_EQ(lobbies.countMatches(), 0) << "Lobby was deleted";
}


TEST_F(ServerIntegrationTest, SimpleMatchNoPlayersEnds) {
    TesterClient host(openClient(), sktserver, lobbies);

    uint8_t id_lobby = host.createClientLobbyDual();
    ASSERT_EQ(id_lobby, 1) << "ID lobby received by client is 1, since its the first match";


    TesterClient joined1(openClient(), sktserver, lobbies);
    TesterClient joined2(openClient(), sktserver, lobbies);

    uint8_t first = joined1.assertJoinLobbySingle(id_lobby, 2);
    uint8_t second = joined2.assertJoinLobbySingle(id_lobby, 3);
    ASSERT_EQ(first, 3) << "ID joined first is correct";
    ASSERT_EQ(second, 4) << "ID joined second is correct";


    host.assertLobbyInfoJoined(first);

    host.assertLobbyInfoJoined(second);
    joined1.assertLobbyInfoJoined(second);

    joined1.close();

    host.assertLobbyInfoLeft(first);
    joined2.assertLobbyInfoLeft(first);

    TesterClient joined3(openClient(), sktserver, lobbies);

    uint8_t fourth = joined3.assertJoinLobbySingle(id_lobby, 3);
    ASSERT_EQ(fourth, 5) << "ID joined fifth is correct";

    host.assertLobbyInfoJoined(fourth);
    joined2.assertLobbyInfoJoined(fourth);

    host.startMatch();

    host.assertLobbyStarted(4);
    joined2.assertLobbyStarted(4);
    joined3.assertLobbyStarted(4);
    ASSERT_EQ(lobbies.countMatches(), 1) << "Lobby was not deleted before it has to";

    host.finish();
    ASSERT_EQ(lobbies.countMatches(), 1) << "Lobby was not deleted before it has to";
    joined2.finish();
    ASSERT_EQ(lobbies.countMatches(), 1) << "Lobby was not deleted before it has to";
    joined3.finish();

    ASSERT_EQ(lobbies.countMatches(), 0) << "Lobby was deleted";
}

TEST_F(ServerIntegrationTest, IntegrationMultiMatchCreate) {

    TesterClient host(openClient(), sktserver, lobbies);
    TesterClient host2(openClient(), sktserver, lobbies);

    uint8_t id_lobby = host.createClientLobbyDual();
    ASSERT_EQ(id_lobby, 1) << "ID lobby received by client is 1, since its the first match";
    ASSERT_EQ(lobbies.countMatches(), 1) << "Lobby was created";

    host.startMatch();

    uint8_t id_lobby2 = host2.createClientLobbyDual();
    ASSERT_EQ(id_lobby2, 2) << "ID lobby received by client is 2";
    ASSERT_EQ(lobbies.countMatches(), 2) << "Lobby was created";

    // 2 is count of players.
    host.assertLobbyStarted(2);
}

TEST_F(ServerIntegrationTest, IntegrationMultiMatchCreateOneCancel) {

    TesterClient host(openClient(), sktserver, lobbies);
    TesterClient host2(openClient(), sktserver, lobbies);

    uint8_t id_lobby = host.createClientLobbyDual();
    ASSERT_EQ(id_lobby, 1) << "ID lobby received by client is 1, since its the first match";
    ASSERT_EQ(lobbies.countMatches(), 1) << "Lobby was created";

    host.finish();

    uint8_t id_lobby2 = host2.createClientLobbyDual();
    ASSERT_EQ(id_lobby2, 2) << "ID lobby received by client is 2";
    ASSERT_EQ(lobbies.countMatches(), 1) << "Lobby was created";
}

TEST_F(ServerIntegrationTest, IntegrationMultiMatchCreateOneCancelAfter) {
    TesterClient host(openClient(), sktserver, lobbies);
    TesterClient host2(openClient(), sktserver, lobbies);

    uint8_t id_lobby = host.createClientLobbyDual();
    ASSERT_EQ(id_lobby, 1) << "ID lobby received by client is 1, since its the first match";
    ASSERT_EQ(lobbies.countMatches(), 1) << "Lobby was created";
    uint8_t id_lobby2 = host2.createClientLobbyDual();
    ASSERT_EQ(id_lobby2, 2) << "ID lobby received by client is 2";
    ASSERT_EQ(lobbies.countMatches(), 2) << "Lobby was created";

    host.finish();

    // Para asegurar sincronia...
    host2.startMatch();

    ASSERT_EQ(lobbies.countMatches(), 1) << "Lobby was cancelled";

    // Importante el esperar sino por ahora se queda colgado.
    host2.assertLobbyStarted(2);
}


TEST_F(ServerIntegrationTest, IntegrationMultiMatchOneEnds) {
    TesterClient host(openClient(), sktserver, lobbies);

    uint8_t id_lobby = host.createClientLobbyDual();
    ASSERT_EQ(id_lobby, 1) << "ID lobby received by client is 1, since its the first match";

    TesterClient host2(openClient(), sktserver, lobbies);
    uint8_t id_lobby2 = host2.createClientLobbyDual();
    ASSERT_EQ(id_lobby2, 2) << "ID lobby received by client is 2";
    ASSERT_EQ(lobbies.countMatches(), 2) << "Lobby was created";


    TesterClient joined1(openClient(), sktserver, lobbies);
    TesterClient joined2(openClient(), sktserver, lobbies);

    uint8_t first = joined1.assertJoinLobbySingle(id_lobby, 2);
    uint8_t second = joined2.assertJoinLobbySingle(id_lobby, 3);
    ASSERT_EQ(first, 3) << "ID joined first is correct";
    ASSERT_EQ(second, 4) << "ID joined second is correct";


    host.assertLobbyInfoJoined(first);

    host.assertLobbyInfoJoined(second);
    joined1.assertLobbyInfoJoined(second);

    joined1.close();

    host.assertLobbyInfoLeft(first);
    joined2.assertLobbyInfoLeft(first);

    TesterClient joined3(openClient(), sktserver, lobbies);

    uint8_t fourth = joined3.assertJoinLobbySingle(id_lobby, 3);
    ASSERT_EQ(fourth, 5) << "ID joined fifth is correct";

    host.assertLobbyInfoJoined(fourth);
    joined2.assertLobbyInfoJoined(fourth);

    host.startMatch();

    host.assertLobbyStarted(4);
    joined2.assertLobbyStarted(4);
    joined3.assertLobbyStarted(4);
    ASSERT_EQ(lobbies.countMatches(), 2) << "Lobby was not deleted before it has to";

    host.finish();
    ASSERT_EQ(lobbies.countMatches(), 2) << "Lobby was not deleted before it has to";
    joined2.finish();
    ASSERT_EQ(lobbies.countMatches(), 2) << "Lobby was not deleted before it has to";
    joined3.finish();

    ASSERT_EQ(lobbies.countMatches(), 1) << "Lobby was deleted";
}


TEST_F(ServerIntegrationTest, IntegrationMultiMatchForceFinish) {
    TesterClient host(openClient(), sktserver, lobbies);

    uint8_t id_lobby = host.createClientLobbyDual();
    ASSERT_EQ(id_lobby, 1) << "ID lobby received by client is 1, since its the first match";

    TesterClient host2(openClient(), sktserver, lobbies);
    uint8_t id_lobby2 = host2.createClientLobbyDual();
    ASSERT_EQ(id_lobby2, 2) << "ID lobby received by client is 2";
    ASSERT_EQ(lobbies.countMatches(), 2) << "Lobby was created";


    TesterClient joined1(openClient(), sktserver, lobbies);
    TesterClient joined2(openClient(), sktserver, lobbies);

    uint8_t first = joined1.assertJoinLobbySingle(id_lobby, 2);
    uint8_t second = joined2.assertJoinLobbySingle(id_lobby, 3);
    ASSERT_EQ(first, 3) << "ID joined first is correct";
    ASSERT_EQ(second, 4) << "ID joined second is correct";


    host.assertLobbyInfoJoined(first);

    host.assertLobbyInfoJoined(second);
    joined1.assertLobbyInfoJoined(second);

    joined1.close();

    host.assertLobbyInfoLeft(first);
    joined2.assertLobbyInfoLeft(first);

    TesterClient joined3(openClient(), sktserver, lobbies);

    uint8_t fourth = joined3.assertJoinLobbySingle(id_lobby, 3);
    ASSERT_EQ(fourth, 5) << "ID joined fifth is correct";

    host.assertLobbyInfoJoined(fourth);
    joined2.assertLobbyInfoJoined(fourth);

    host.startMatch();

    host.assertLobbyStarted(4);
    joined2.assertLobbyStarted(4);
    joined3.assertLobbyStarted(4);

    std::cout << "-------------> FINISH ALL!" << std::endl;
    lobbies.finishAll();


    host.finish();
    joined2.finish();
    joined3.finish();

    host2.assertLobbyCanceled();
    host2.finish();
    // host2.assertLobbyError(UNKNOWN);
    ASSERT_EQ(lobbies.countMatches(), 0) << "Lobby was deleted";
}
