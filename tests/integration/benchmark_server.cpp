#include <iostream>

#include "./testerclient.h"
#include "common/core/liberror.h"
#include "gmock/gmock.h"
#include "common/clock.h"
#include "gtest/gtest.h"
#include "server/lobbycontainer.h"

#include "common/clientprotocol.h"
#include "common/serverprotocol.h"

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
    std::cout << "------------------> BENCHMARK START!\n";
    Clock clock(30);
    clock.resetnow();
    
    
    while(count > 0){
        host.assertRecvState(stats, state);
        joined1.assertRecvState(stats, state);
        joined2.assertRecvState(stats, state);
        count--;
    }


    int ms = clock.measure();
    std::cout << "--->TOOK MS " << ms << "ms "<< std::endl;

}



TEST_F(BenchmarkServer, ProtocolMatchdtoSend) {
    MatchDto state;

    //                      id,alive, x , y, move_action
    state.players.emplace_back(3, true, 10, 5, TypeMoveAction::MOVE_LEFT);
    PlayerDTO& player2 = state.players.emplace_back(2, false, 5, 0, TypeMoveAction::AIR_LEFT);
    
    state.players.emplace_back(4, true, 50, 5, TypeMoveAction::MOVE_LEFT);
    state.players.emplace_back(5, true, 13, 5, TypeMoveAction::MOVE_LEFT);

    state.objects.emplace_back(5, 5, TypeDynamicObject::BOX);
    state.objects.emplace_back(10, 5, TypeDynamicObject::BOX);
    player2.pos.x = 10;
    player2.pos.y = 15;

    // Los protocols se encargan. De liberar el shared socket.
    Socket client_skt = openClient();
    Socket server_skt = sktserver.accept();
    
    ClientProtocol client(client_skt);
    ServerProtocol server(server_skt);

    MatchDto state_recv;
    MatchStatsInfo stats_recv;
    
    int count = 240;
    Clock clock(30);
    clock.resetnow();
    
    while(count > 0){
        server.sendstate(state);
        
        player2.pos.x++;
        player2.pos.y++;

        ASSERT_TRUE(client.recvstate(stats_recv, state_recv));
        count--;
    }
    

    int ms = clock.measure();
    std::cout << "--->TOOK " << ms << "ms "<< std::endl;
    
}
