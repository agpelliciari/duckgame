#include <iostream>

#include "./testerclient.h"
#include "common/core/liberror.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "server/lobbycontainer.h"

using ::testing::InSequence;
using ::testing::ThrowsMessage;

class TestIntegrationLobby: public ::testing::Test {
protected:
    Socket sktserver;
    LobbyContainer lobbies;
    std::string mapusing;

    inline TestIntegrationLobby(): sktserver("4096"), lobbies("res/maps/test/", "res/configs.yaml"), mapusing("testdivided") {}

    Socket openClient() { return Socket(NULL, "4096"); }

    virtual ~TestIntegrationLobby() {
        sktserver.shutdown(2);
        sktserver.close();
    }
};


TEST_F(TestIntegrationLobby, SimpleCreateLobbyDual) {

    TesterClient host(openClient(), sktserver, lobbies);

    std::cout << "CREATE LOBBY DUAL?!\n";
    uint8_t id_lobby = host.createClientLobbyDual(lobbies.registeredMaps());
    ASSERT_EQ(id_lobby, 1) << "ID lobby received by client is 1, since its the first match";
    //ASSERT_EQ(lobbies.countMatches(), 1) << "Lobby was created";

    std::cout << "START MATCH?!\n";
    host.startMatch(mapusing);

    std::cout << "ASSERT STARTED MATCH?!\n";
    // 2 is count of players.
    host.assertLobbyStarted(2);
    std::cout << "END ?!?!\n";
}

TEST_F(TestIntegrationLobby, SimpleCreateLobbyDualInmediateDisconnect) {

    TesterClient host(openClient(), sktserver, lobbies);

    uint8_t id_lobby = host.createClientLobbyDual(lobbies.registeredMaps());
    ASSERT_EQ(id_lobby, 1) << "ID lobby received by client is 1, since its the first match";
    //ASSERT_EQ(lobbies.countMatches(), 1) << "Lobby was created";

    host.startMatch(mapusing);
    host.close();
}

/*
// Ahora esto traeria problemas, ya que no esta full definido que se hace
// definitivamente 1 player no se podria
TEST_F(TestIntegrationLobby, SimpleCreateLobbySingle) {

    TesterClient host(openClient(), sktserver, lobbies);

    uint8_t id_lobby = host.createClientLobbySingle(lobbies.registeredMaps());
    ASSERT_EQ(id_lobby, 1) << "ID lobby received by client is 1, since its the first match";
    host.startMatch(mapusing);

    // 1 is count of players. Should not start maybe?
    host.assertLobbyStarted(1);
}
*/


TEST_F(TestIntegrationLobby, SimpleCreateLobbyAndJoin) {
    TesterClient host(openClient(), sktserver, lobbies);

    uint8_t id_lobby = host.createClientLobbySingle(lobbies.registeredMaps());
    ASSERT_EQ(id_lobby, 1) << "ID lobby received by client is 1, since its the first match";


    TesterClient joined1(openClient(), sktserver, lobbies);

    uint8_t first = 0;
    uint8_t second = joined1.assertJoinLobbyDual(id_lobby, 3, &first);

    ASSERT_EQ(first, 1) << "ID joined first is correct";
    ASSERT_EQ(second, 2) << "ID joined second is correct";

    host.assertLobbyInfoJoined(first);
    host.assertLobbyInfoJoined(second);

    host.startMatch(mapusing);
    std::cout << "STARTED?!\n";

    // 1 is count of players. Should not start maybe?
    host.assertLobbyStarted(3);
    joined1.assertLobbyStarted(3);
    
    std::cout << "FINISHED TEST?!\n";
}

TEST_F(TestIntegrationLobby, JoinFailedNotFound) {
    TesterClient joined1(openClient(), sktserver, lobbies);

    LobbyErrorType error = joined1.assertJoinLobbyFail(23);

    ASSERT_EQ(error, LOBBY_NOT_FOUND) << "Error type was lobby not found";
}


TEST_F(TestIntegrationLobby, SimpleCreateLobbyAndJoinSingle) {
    TesterClient host(openClient(), sktserver, lobbies);

    uint8_t id_lobby = host.createClientLobbySingle(lobbies.registeredMaps());
    ASSERT_EQ(id_lobby, 1) << "ID lobby received by client is 1, since its the first match";


    TesterClient joined1(openClient(), sktserver, lobbies);

    uint8_t first = joined1.assertJoinLobbySingle(id_lobby, 2);
    ASSERT_EQ(first, 1) << "ID joined first is correct";

    host.assertLobbyInfoJoined(first);

    host.startMatch(mapusing);

    // 1 is count of players. Should not start maybe?
    host.assertLobbyStarted(2);
    joined1.assertLobbyStarted(2);
}


TEST_F(TestIntegrationLobby, SimpleCreateLobbyAndJoinButLeft) {
    TesterClient host(openClient(), sktserver, lobbies);

    uint8_t id_lobby = host.createClientLobbyDual(lobbies.registeredMaps());
    ASSERT_EQ(id_lobby, 1) << "ID lobby received by client is 1, since its the first match";


    TesterClient joined1(openClient(), sktserver, lobbies);

    uint8_t first = 0;
    uint8_t second = joined1.assertJoinLobbyDual(id_lobby, 4, &first);

    ASSERT_EQ(first, 2) << "ID joined first is correct";
    ASSERT_EQ(second, 3) << "ID joined second is correct";

    host.assertLobbyInfoJoined(first);
    host.assertLobbyInfoJoined(second);
    std::cout << "----------------------> ASSERTED JOINED\n";
    joined1.close();
    host.assertLobbyInfoLeft(first);
    host.assertLobbyInfoLeft(second);

    std::cout << "----------------------> ASSERTED LEFT\n";
    host.startMatch(mapusing);

    host.assertLobbyStarted(2);
    std::cout << "----------------------> ASSERTED STARTED\n";
    
}


TEST_F(TestIntegrationLobby, SimpleJoinMultiple) {
    TesterClient host(openClient(), sktserver, lobbies);

    uint8_t id_lobby = host.createClientLobbyDual(lobbies.registeredMaps());
    ASSERT_EQ(id_lobby, 1) << "ID lobby received by client is 1, since its the first match";


    TesterClient joined1(openClient(), sktserver, lobbies);
    TesterClient joined2(openClient(), sktserver, lobbies);

    uint8_t first = joined1.assertJoinLobbySingle(id_lobby, 3);
    uint8_t second = joined2.assertJoinLobbySingle(id_lobby, 4);
    ASSERT_EQ(first, 2) << "ID joined first is correct";
    ASSERT_EQ(second, 3) << "ID joined second is correct";


    host.assertLobbyInfoJoined(first);

    host.assertLobbyInfoJoined(second);
    joined1.assertLobbyInfoJoined(second);

    host.startMatch(mapusing);

    host.assertLobbyStarted(4);
    joined1.assertLobbyStarted(4);
    joined2.assertLobbyStarted(4);
}


TEST_F(TestIntegrationLobby, SimpleJoinMultipleWithLeaves) {
    TesterClient host(openClient(), sktserver, lobbies);

    uint8_t id_lobby = host.createClientLobbyDual(lobbies.registeredMaps());
    ASSERT_EQ(id_lobby, 1) << "ID lobby received by client is 1, since its the first match";


    TesterClient joined1(openClient(), sktserver, lobbies);
    TesterClient joined2(openClient(), sktserver, lobbies);

    uint8_t first = joined1.assertJoinLobbySingle(id_lobby, 3);
    uint8_t second = joined2.assertJoinLobbySingle(id_lobby, 4);
    ASSERT_EQ(first, 2) << "ID joined first is correct";
    ASSERT_EQ(second, 3) << "ID joined second is correct";


    host.assertLobbyInfoJoined(first);

    host.assertLobbyInfoJoined(second);
    joined1.assertLobbyInfoJoined(second);

    joined1.close();

    host.assertLobbyInfoLeft(first);
    joined2.assertLobbyInfoLeft(first);

    TesterClient joined3(openClient(), sktserver, lobbies);

    uint8_t fourth = joined3.assertJoinLobbySingle(id_lobby, 4);
    ASSERT_EQ(fourth, 3) << "ID joined fifth is correct, third since one left";

    host.assertLobbyInfoJoined(fourth);
    joined2.assertLobbyInfoJoined(fourth);

    host.startMatch(mapusing);

    host.assertLobbyStarted(4);
    joined2.assertLobbyStarted(4);
    joined3.assertLobbyStarted(4);
}

TEST_F(TestIntegrationLobby, SimpleCreateLobbyAndJoinCancel) {
    TesterClient host(openClient(), sktserver, lobbies);

    uint8_t id_lobby = host.createClientLobbySingle(lobbies.registeredMaps());
    ASSERT_EQ(id_lobby, 1) << "ID lobby received by client is 1, since its the first match";


    TesterClient joined1(openClient(), sktserver, lobbies);

    uint8_t first = 0;
    uint8_t second = joined1.assertJoinLobbyDual(id_lobby, 3, &first);

    ASSERT_EQ(first, 1) << "ID joined first is correct";
    ASSERT_EQ(second, 2) << "ID joined second is correct";

    host.assertLobbyInfoJoined(first);
    host.assertLobbyInfoJoined(second);

    // host.startMatch(mapusing);

    // 1 is count of players. Should not start maybe?
    host.finish();

    joined1.assertLobbyHostLeft();
    ASSERT_FALSE(host.isReceiverOpen()) << "receiver protocol was not open";

    joined1.finish();  // Sincronismo. Sino hay una race condition
    ASSERT_FALSE(joined1.isReceiverOpen()) << "receiver protocol was not open";
    //ASSERT_EQ(lobbies.countMatches(), 0) << "Lobby was deleted";
}

TEST_F(TestIntegrationLobby, SimpleJoinMultipleCancel) {
    TesterClient host(openClient(), sktserver, lobbies);

    uint8_t id_lobby = host.createClientLobbyDual(lobbies.registeredMaps());
    ASSERT_EQ(id_lobby, 1) << "ID lobby received by client is 1, since its the first match";


    TesterClient joined1(openClient(), sktserver, lobbies);
    TesterClient joined2(openClient(), sktserver, lobbies);

    uint8_t first = joined1.assertJoinLobbySingle(id_lobby, 3);
    uint8_t second = joined2.assertJoinLobbySingle(id_lobby, 4);
    ASSERT_EQ(first, 2) << "ID joined first is correct";
    ASSERT_EQ(second, 3) << "ID joined second is correct";


    host.assertLobbyInfoJoined(first);

    host.assertLobbyInfoJoined(second);
    joined1.assertLobbyInfoJoined(second);

    host.finish();

    joined1.assertLobbyHostLeft();

    joined2.assertLobbyHostLeft();

    joined1.finish();
    joined2.finish();  // Para garantizar sincronismo. Antes de verificar el delete.
    ASSERT_FALSE(joined1.isReceiverOpen()) << "receiver protocol was not open";
    ASSERT_FALSE(joined2.isReceiverOpen()) << "receiver protocol was not open";

    //ASSERT_EQ(lobbies.countMatches(), 0) << "Lobby was deleted";
}


TEST_F(TestIntegrationLobby, SimpleMatchNoPlayersEnds) {
    TesterClient host(openClient(), sktserver, lobbies);

    uint8_t id_lobby = host.createClientLobbyDual(lobbies.registeredMaps());
    ASSERT_EQ(id_lobby, 1) << "ID lobby received by client is 1, since its the first match";


    TesterClient joined1(openClient(), sktserver, lobbies);
    TesterClient joined2(openClient(), sktserver, lobbies);

    uint8_t first = joined1.assertJoinLobbySingle(id_lobby, 3);
    uint8_t second = joined2.assertJoinLobbySingle(id_lobby, 4);
    ASSERT_EQ(first, 2) << "ID joined first is correct";
    ASSERT_EQ(second, 3) << "ID joined second is correct";


    host.assertLobbyInfoJoined(first);

    host.assertLobbyInfoJoined(second);
    joined1.assertLobbyInfoJoined(second);

    joined1.close();

    host.assertLobbyInfoLeft(first);
    joined2.assertLobbyInfoLeft(first);

    TesterClient joined3(openClient(), sktserver, lobbies);

    uint8_t fourth = joined3.assertJoinLobbySingle(id_lobby, 4);
    ASSERT_EQ(fourth, 3) << "ID joined fifth is correct";

    host.assertLobbyInfoJoined(fourth);
    joined2.assertLobbyInfoJoined(fourth);

    host.startMatch(mapusing);

    host.assertLobbyStarted(4);
    joined2.assertLobbyStarted(4);
    joined3.assertLobbyStarted(4);
    //ASSERT_EQ(lobbies.countMatches(), 1) << "Lobby was not deleted before it has to";

    host.finish();

    ASSERT_FALSE(host.isReceiverOpen()) << "receiver protocol was not open";
    //ASSERT_EQ(lobbies.countMatches(), 1) << "Lobby was not deleted before it has to";


    // ASSERT_FALSE(joined2.isReceiverOpen()) << "receiver protocol was not open";
    joined2.finish();

    //ASSERT_EQ(lobbies.countMatches(), 1) << "Lobby was not deleted before it has to";
    // ASSERT_FALSE(joined3.isReceiverOpen()) << "receiver protocol was not open";
    joined3.finish();
    //ASSERT_EQ(lobbies.countMatches(), 0) << "Lobby was deleted";
}

TEST_F(TestIntegrationLobby, IntegrationMultiMatchCreate) {

    TesterClient host(openClient(), sktserver, lobbies);
    TesterClient host2(openClient(), sktserver, lobbies);

    uint8_t id_lobby = host.createClientLobbyDual(lobbies.registeredMaps());
    ASSERT_EQ(id_lobby, 1) << "ID lobby received by client is 1, since its the first match";
    //ASSERT_EQ(lobbies.countMatches(), 1) << "Lobby was created";

    host.startMatch(mapusing);

    uint8_t id_lobby2 = host2.createClientLobbyDual(lobbies.registeredMaps());
    ASSERT_EQ(id_lobby2, 2) << "ID lobby received by client is 2";
    //ASSERT_EQ(lobbies.countMatches(), 2) << "Lobby was created";

    // 2 is count of players.
    host.assertLobbyStarted(2);
}

TEST_F(TestIntegrationLobby, IntegrationMultiMatchCreateOneCancel) {

    TesterClient host(openClient(), sktserver, lobbies);
    TesterClient host2(openClient(), sktserver, lobbies);

    uint8_t id_lobby = host.createClientLobbyDual(lobbies.registeredMaps());
    ASSERT_EQ(id_lobby, 1) << "ID lobby received by client is 1, since its the first match";
    //ASSERT_EQ(lobbies.countMatches(), 1) << "Lobby was created";

    host.finish();
    ASSERT_FALSE(host.isReceiverOpen()) << "receiver protocol was not open";

    uint8_t id_lobby2 = host2.createClientLobbyDual(lobbies.registeredMaps());
    ASSERT_EQ(id_lobby2, 2) << "ID lobby received by client is 2";
    //ASSERT_EQ(lobbies.countMatches(), 1) << "Lobby was created";
}

TEST_F(TestIntegrationLobby, IntegrationMultiMatchCreateOneCancelAfter) {
    TesterClient host(openClient(), sktserver, lobbies);
    TesterClient host2(openClient(), sktserver, lobbies);

    uint8_t id_lobby = host.createClientLobbyDual(lobbies.registeredMaps());
    ASSERT_EQ(id_lobby, 1) << "ID lobby received by client is 1, since its the first match";
    //ASSERT_EQ(lobbies.countMatches(), 1) << "Lobby was created";
    uint8_t id_lobby2 = host2.createClientLobbyDual(lobbies.registeredMaps());
    ASSERT_EQ(id_lobby2, 2) << "ID lobby received by client is 2";
    //ASSERT_EQ(lobbies.countMatches(), 2) << "Lobby was created";

    host.finish();
    ASSERT_FALSE(host.isReceiverOpen()) << "receiver protocol was not open";

    // Para asegurar sincronia...
    host2.startMatch(mapusing);

    //ASSERT_EQ(lobbies.countMatches(), 1) << "Lobby was cancelled";

    // Importante el esperar sino por ahora se queda colgado.
    host2.assertLobbyStarted(2);
}


TEST_F(TestIntegrationLobby, IntegrationMultiMatchOneEnds) {
    TesterClient host(openClient(), sktserver, lobbies);

    uint8_t id_lobby = host.createClientLobbyDual(lobbies.registeredMaps());
    ASSERT_EQ(id_lobby, 1) << "ID lobby received by client is 1, since its the first match";

    TesterClient host2(openClient(), sktserver, lobbies);
    uint8_t id_lobby2 = host2.createClientLobbyDual(lobbies.registeredMaps());
    ASSERT_EQ(id_lobby2, 2) << "ID lobby received by client is 2";
    //ASSERT_EQ(lobbies.countMatches(), 2) << "Lobby was created";


    TesterClient joined1(openClient(), sktserver, lobbies);
    TesterClient joined2(openClient(), sktserver, lobbies);

    uint8_t first = joined1.assertJoinLobbySingle(id_lobby, 3);
    uint8_t second = joined2.assertJoinLobbySingle(id_lobby, 4);
    ASSERT_EQ(first, 2) << "ID joined first is correct";
    ASSERT_EQ(second, 3) << "ID joined second is correct";


    host.assertLobbyInfoJoined(first);

    host.assertLobbyInfoJoined(second);
    joined1.assertLobbyInfoJoined(second);

    joined1.close();

    host.assertLobbyInfoLeft(first);
    joined2.assertLobbyInfoLeft(first);

    TesterClient joined3(openClient(), sktserver, lobbies);

    uint8_t fourth = joined3.assertJoinLobbySingle(id_lobby, 4);
    ASSERT_EQ(fourth, 3) << "ID joined fifth is correct";

    host.assertLobbyInfoJoined(fourth);
    joined2.assertLobbyInfoJoined(fourth);

    host.startMatch(mapusing);

    host.assertLobbyStarted(4);
    joined2.assertLobbyStarted(4);
    joined3.assertLobbyStarted(4);
    //ASSERT_EQ(lobbies.countMatches(), 2) << "Lobby was not deleted before it has to";

    host.finish();
    ASSERT_FALSE(host.isReceiverOpen()) << "receiver protocol was not open";

    //ASSERT_EQ(lobbies.countMatches(), 2) << "Lobby was not deleted before it has to";
    // ASSERT_FALSE(joined2.isReceiverOpen()) << "receiver protocol was not open";
    joined2.finish();
    //ASSERT_EQ(lobbies.countMatches(), 2) << "Lobby was not deleted before it has to";
    // ASSERT_FALSE(joined3.isReceiverOpen()) << "receiver protocol was not open";

    joined3.finish();

    //ASSERT_EQ(lobbies.countMatches(), 1) << "Lobby was deleted";
}


TEST_F(TestIntegrationLobby, IntegrationMultiMatchForceFinish) {
    TesterClient host(openClient(), sktserver, lobbies);

    uint8_t id_lobby = host.createClientLobbyDual(lobbies.registeredMaps());
    ASSERT_EQ(id_lobby, 1) << "ID lobby received by client is 1, since its the first match";

    TesterClient host2(openClient(), sktserver, lobbies);
    uint8_t id_lobby2 = host2.createClientLobbyDual(lobbies.registeredMaps());
    ASSERT_EQ(id_lobby2, 2) << "ID lobby received by client is 2";
    //ASSERT_EQ(lobbies.countMatches(), 2) << "Lobby was created";


    TesterClient joined1(openClient(), sktserver, lobbies);
    TesterClient joined2(openClient(), sktserver, lobbies);

    uint8_t first = joined1.assertJoinLobbySingle(id_lobby, 3);
    uint8_t second = joined2.assertJoinLobbySingle(id_lobby, 4);
    ASSERT_EQ(first, 2) << "ID joined first is correct";
    ASSERT_EQ(second, 3) << "ID joined second is correct";


    host.assertLobbyInfoJoined(first);

    host.assertLobbyInfoJoined(second);
    joined1.assertLobbyInfoJoined(second);

    joined1.close();

    host.assertLobbyInfoLeft(first);
    joined2.assertLobbyInfoLeft(first);

    TesterClient joined3(openClient(), sktserver, lobbies);

    uint8_t fourth = joined3.assertJoinLobbySingle(id_lobby, 4);
    ASSERT_EQ(fourth, 3) << "ID joined fifth is correct";

    host.assertLobbyInfoJoined(fourth);
    joined2.assertLobbyInfoJoined(fourth);

    host.startMatch(mapusing);

    host.assertLobbyStarted(4);
    joined2.assertLobbyStarted(4);
    joined3.assertLobbyStarted(4);

    lobbies.finishAll();

    // ASSERT_FALSE(host.isReceiverOpen()) << "receiver protocol was not open";
    // ASSERT_FALSE(joined2.isReceiverOpen()) << "receiver protocol was not open";
    // ASSERT_FALSE(joined3.isReceiverOpen()) << "receiver protocol was not open";

    //host.finish();
    //joined2.finish();
    //joined3.finish();

    EXPECT_THROW(host2.assertLobbyError(), LibError) << "Error type is server error, since forced finish";
    ASSERT_FALSE(host2.isReceiverOpen()) << "receiver protocol was not open";
    // host2.assertLobbyError(UNKNOWN);
    
    // No los libera hasta el destructor, total la 'q' cierra el server.
    //ASSERT_EQ(lobbies.countMatches(), 0) << "Lobby was deleted";
}


TEST_F(TestIntegrationLobby, SimpleCreateLobbyAndJoinAfterStartedFails) {
    TesterClient host(openClient(), sktserver, lobbies);

    uint8_t id_lobby = host.createClientLobbyDual(lobbies.registeredMaps());
    ASSERT_EQ(id_lobby, 1) << "ID lobby received by client is 1, since its the first match";


    host.startMatch(mapusing);

    host.assertLobbyStarted(2);

    TesterClient joined1(openClient(), sktserver, lobbies);

    LobbyErrorType error = joined1.assertJoinLobbyFail(id_lobby);

    ASSERT_EQ(error, LOBBY_ALREADY_STARTED) << "Error type was lobby already started";
}
