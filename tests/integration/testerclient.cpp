#include "./testerclient.h"

#include <utility>

#include "gtest/gtest.h"

TesterClient::TesterClient(Socket&& _client, Socket& _serv, LobbyContainer& lobbies):
        sktclient(std::move(_client)),
        sktcontrol(_serv.accept()),
        client(sktclient),
        receiver(std::nullopt) {

    receiver.emplace(lobbies, sktcontrol);
    receiver.value().init();
}

uint8_t TesterClient::createClientLobbyDual() {
    uint8_t id_lobby = client.createLobby();

    uint8_t first = 0;
    uint8_t second = client.setdualplay(&first);

    EXPECT_EQ(first, 1) << "ID first player is 1, since its the first on the match";
    EXPECT_EQ(second, 2) << "ID first player is 2, since its the second on the match";
    return id_lobby;
}

uint8_t TesterClient::createClientLobbySingle() {
    uint8_t id_lobby = client.createLobby();
    uint8_t first = client.setsingleplay();
    EXPECT_EQ(first, 1) << "ID first player is 1, since its the first on the match";
    return id_lobby;
}


void TesterClient::assertLobbyStarted(uint8_t count) {
    lobby_info info;
    client.recvlobbyinfo(info);

    EXPECT_EQ(info.action, (uint8_t)LobbyResponseType::STARTED_LOBBY)
            << "INITED Match succesfully ";
    EXPECT_EQ(info.data, count) << "Total count at start is correct";
}

void TesterClient::assertLobbyHostLeft() {
    EXPECT_EQ(assertLobbyError(), ANFITRION_LEFT) << "Error code is anfitrion left.";
}

LobbyErrorType TesterClient::assertLobbyError() {
    lobby_info info;
    client.recvlobbyinfo(info);

    EXPECT_EQ(info.action, LobbyResponseType::GAME_ERROR) << "Type info is error";
    return (LobbyErrorType)info.data;
}


void TesterClient::assertLobbyInfoJoined(uint8_t id) {
    lobby_info info;
    client.recvlobbyinfo(info);
    EXPECT_EQ(info.action, LobbyResponseType::PLAYER_NEW) << "client was notified about a join";
    EXPECT_EQ(info.data, id) << "Id of joined is correct";
}

void TesterClient::assertLobbyInfoLeft(uint8_t id) {
    lobby_info info;
    client.recvlobbyinfo(info);
    EXPECT_EQ(info.action, LobbyResponseType::PLAYER_LEFT) << "client was notified about a join";
    EXPECT_EQ(info.data, id) << "Id of joined is correct";
}


// Metodos para el arrange en tests.
uint8_t TesterClient::assertJoinLobbySingle(uint8_t id_lobby, uint8_t count) {
    lobby_info info = client.joinLobby(id_lobby);
    EXPECT_EQ(info.action, LobbyResponseType::JOINED_LOBBY) << "Joined Match succesfully ";
    EXPECT_EQ(info.data, count) << "Total count is correct?";
    return client.setsingleplay();
}

LobbyErrorType TesterClient::assertJoinLobbyFail(uint8_t id_lobby) {
    lobby_info info = client.joinLobby(id_lobby);
    EXPECT_EQ(info.action, LobbyResponseType::GAME_ERROR) << "Joined response is game error";
    return (LobbyErrorType)info.data;
}


uint8_t TesterClient::assertJoinLobbyDual(uint8_t id_lobby, uint8_t count, uint8_t* first) {
    lobby_info info = client.joinLobby(id_lobby);
    EXPECT_EQ(info.action, LobbyResponseType::JOINED_LOBBY) << "Joined Match succesfully ";
    EXPECT_EQ(info.data, count) << "Total count is correct?";

    return client.setdualplay(first);
}


void TesterClient::startMatch() { client.sendlobbyaction({PLAYER_READY, 0}); }

ClientProtocol& TesterClient::getClient() { return client; }

void TesterClient::close() {
    sktclient.finish();
    // receiver.reset();
    // sktserver.close();
    // client.close();
}

void TesterClient::finish() {
    sktclient.finish();
    receiver.reset();
}
