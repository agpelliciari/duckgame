#include <iostream>

#include "./testerclient.h"
#include "common/core/liberror.h"
#include "gmock/gmock.h"
#include "common/clock.h"
#include "gtest/gtest.h"
#include "server/lobbycontainer.h"

using ::testing::InSequence;
using ::testing::ThrowsMessage;



class BenchmarkServer: public ::testing::Test {
protected:
    Socket sktserver;
    LobbyContainer lobbies;
    std::string mapusing;

    inline BenchmarkServer(): sktserver("4096"), lobbies("res/maps/test/", "res/configs.yaml"), mapusing("testdivided") {}

    Socket openClient() { return Socket(NULL, "4096"); }

    virtual ~BenchmarkServer() {
        sktserver.shutdown(2);
        sktserver.close();
    }
};

TEST_F(BenchmarkServer, SimpleJoinMultiple) {
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
    
    MatchStatsInfo stats;
    MatchDto state;
    int count = 120;
    Clock clock(30);
    clock.resetnow();
    
    while(count > 0){
        host.assertRecvState(stats, state);
        joined1.assertRecvState(stats, state);
        joined2.assertRecvState(stats, state);
        count--;
    }


    int ms = clock.measure();
    std::cout << "--->TOOK " << ms << "ms "<< std::endl;

}

/*
TEST_F(BenchmarkServer, SimpleJoinMultipleWithLeaves) {
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

*/
