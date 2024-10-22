#include "client/lobbycreatemode.h"
#include "common/protocolerror.h"
#include <iostream>

LobbyCreateMode::LobbyCreateMode(uint8_t _count) : playercount(_count){

}

void LobbyCreateMode::exec(ClientProtocol& protocol){
      protocol.createLobby(playercount);
      std::cerr << "press enter to start the match!" << std::endl;
      std::string action;
      if (!(std::cin >> action)) {  // Could not read if new lobby.
          throw ProtocolError("Did not read match start!!");
      }

      protocol.startlobby();
}
