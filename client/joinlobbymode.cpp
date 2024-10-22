#include "client/joinlobbymode.h"
#include <iostream>
JoinLobbyMode::JoinLobbyMode(uint8_t _count, uint8_t id) : playercount(_count), idlobby(id){

}


void JoinLobbyMode::exec(ClientProtocol& protocol){
      std::cerr << "lobby id to join: "<<(int)idlobby << std::endl;
      protocol.joinLobby(playercount, idlobby);
}
