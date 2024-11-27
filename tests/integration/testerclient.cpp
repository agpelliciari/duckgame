#include "./testerclient.h"

#include <utility>
#include <vector>
#include "common/dtosgame.h"

#include "gtest/gtest.h"

TesterClient::TesterClient(Socket&& _client, Socket& _serv, LobbyContainer& lobbies):
        sktclient(std::move(_client)),
        sktcontrol(_serv.accept()),
        client(sktclient),
        receiver(std::nullopt) {

    receiver.emplace(lobbies, sktcontrol);
    receiver.value().init();
}

uint8_t TesterClient::createClientLobbyDual(const std::vector<std::string>& lobby_maps) {
    std::vector<std::string> maps;
    uint8_t id_lobby = client.sendCreateLobby(2,maps);

    uint8_t first = 0;
    uint8_t second = client.recvIDDualPlayer(&first);

    EXPECT_EQ(first, 0) << "ID first player is 0, since its the first on the match";
    EXPECT_EQ(second, 1) << "ID first player is 1, since its the second on the match";
    
    EXPECT_EQ(maps.size(), lobby_maps.size()) << "Client received all maps";
    auto iterRecv = maps.begin();
    auto iterMap  = lobby_maps.begin();
    int ind = 0;
    while(iterMap != lobby_maps.end()){
        EXPECT_EQ(*iterRecv, *iterMap) << "Map id "<< ind << "is the same";
        ++iterRecv;
        ++iterMap;
        ind++;
    }
    
    
    return id_lobby;
}

void TesterClient::assertRecvState(MatchStatsInfo& stats, MatchDto& state){
    client.recvstate(stats, state);
}


uint8_t TesterClient::createClientLobbySingle(const std::vector<std::string>& lobby_maps) {
    std::vector<std::string> maps;
    uint8_t id_lobby = client.sendCreateLobby(1,maps);
    uint8_t first = client.recvIDSinglePlayer();
    EXPECT_EQ(first, 0) << "ID first player is 0, since its the first on the match";

    EXPECT_EQ(maps.size(), lobby_maps.size()) << "Client received all maps";
    auto iterRecv = maps.begin();
    auto iterMap  = lobby_maps.begin();
    int ind = 0;
    while(iterMap != lobby_maps.end()){
        EXPECT_EQ(*iterRecv, *iterMap) << "Map id "<< ind << "is the same";
        ++iterRecv;
        ++iterMap;
        ind++;
    }

    
    return id_lobby;
}


void TesterClient::assertLobbyStarted(uint8_t count) {
    lobby_info info;
    client.recvlobbyinfo(info);

    EXPECT_EQ((int)info.action, (int)LobbyResponseType::STARTED_LOBBY)
            << "INITED Match succesfully ";
    EXPECT_EQ(info.data, count) << "Total count at start is correct";
    
    
    // Chequea map info
    struct MapData map;
    client.recvmapdata(map);
    
    
    // Y tambien chequea el stats info para el primero
    MatchDto upd;
    MatchStatsInfo stats;
    EXPECT_FALSE(client.recvstate(stats,upd));
    
    std::cout << "RECV S "<< stats.parse()<<std::endl;
    EXPECT_EQ(stats.state, STARTED_ROUND);
    EXPECT_EQ(stats.numronda, 1);
    
}

void TesterClient::assertLobbyHostLeft() {
    EXPECT_EQ(assertLobbyError(), ANFITRION_LEFT) << "Error code is anfitrion left.";
}

LobbyErrorType TesterClient::assertLobbyError() {
    lobby_info info;
    client.recvlobbyinfo(info);

    EXPECT_EQ((int)info.action, (int)LobbyResponseType::GAME_ERROR) << "Type info is error";
    return (LobbyErrorType)info.data;
}

void TesterClient::assertLobbyInfoJoined(uint8_t id) {
    lobby_info info;
    client.recvlobbyinfo(info);
    EXPECT_EQ((int)info.action, (int)LobbyResponseType::PLAYER_NEW) << "client was notified about a join";
    EXPECT_EQ(info.data, id) << "Id of joined is correct";
}

void TesterClient::assertLobbyInfoLeft(uint8_t id) {
    lobby_info info;
    client.recvlobbyinfo(info);
    EXPECT_EQ((int)info.action, (int)LobbyResponseType::PLAYER_LEFT) << "client was notified about a join";
    EXPECT_EQ(info.data, id) << "Id of joined is correct";
}


// Metodos para el arrange en tests.
uint8_t TesterClient::assertJoinLobbySingle(uint8_t id_lobby, uint8_t count) {
    
    lobby_info info = client.sendJoinLobby(id_lobby, 1);
    EXPECT_EQ((int)info.action, (int)LobbyResponseType::JOINED_LOBBY) << "Joined Match succesfully ";
    EXPECT_EQ(info.data, count) << "Total count is correct?";
    
    
    return client.recvIDSinglePlayer();
}

LobbyErrorType TesterClient::assertJoinLobbyFail(uint8_t id_lobby) {
    lobby_info info = client.sendJoinLobby(id_lobby, 2);
    EXPECT_EQ((int)info.action, (int)LobbyResponseType::GAME_ERROR) << "Joined response is game error";
    return (LobbyErrorType)info.data;
}


uint8_t TesterClient::assertJoinLobbyDual(uint8_t id_lobby, uint8_t count, uint8_t* first) {
    std::cout << "SHOULD JOIN DUAL\n";
    lobby_info info = client.sendJoinLobby(id_lobby, 2);
    std::cout << "SENT AND RECEIVED JOIN RSPS\n";
    EXPECT_EQ((int)info.action, (int)LobbyResponseType::JOINED_LOBBY) << "Joined Match succesfully ";
    EXPECT_EQ(info.data, count) << "Total count is correct?";

    return client.recvIDDualPlayer(first);
}


void TesterClient::startMatch(const std::string& map) {
    client.sendlobbyaction({PLAYER_READY, 0});
    client.sendmapname(map);
}

ClientProtocol& TesterClient::getClient() { return client; }

void TesterClient::close() {
    sktclient.finish();
    // receiver.reset();
    // sktserver.close();
    // client.close();
}

bool TesterClient::isReceiverOpen() { return receiver->isopen(); }

void TesterClient::finish() {
    client.close();
    // sktclient.finish();
    receiver.reset();
}

TesterClient::~TesterClient() { finish(); }
