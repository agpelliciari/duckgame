#include "./clientprotocol.h"

#include <iostream>
#include <string>
#include <utility>

#include "common/core/liberror.h"


ClientProtocol::ClientProtocol(Messenger& conn): protocol(conn) {}


void ClientProtocol::recvlobbyinfo(lobby_info& out) {
    // Podria tirar cast error.
    out.action = (LobbyResponseType)protocol.recvbyte();
    out.data = protocol.recvbyte();
    // throw ProtocolError("Invalid lobby info action!");
}


void ClientProtocol::sendaction(PlayerActionDTO& action) {
    protocol.sendbytes(&action, sizeof(action));
}

lobby_info ClientProtocol::sendJoinLobby(const uint8_t id_match, const uint8_t count) {
    uint8_t info[3] = {LobbyActionType::JOIN_LOBBY, count, id_match};
    protocol.sendbytes(&info, sizeof(info));
    lobby_info out;
    
    recvlobbyinfo(out);
    
    if (out.action != JOINED_LOBBY && out.action != GAME_ERROR) {
        out.action = GAME_ERROR;
        out.data = LobbyErrorType::UNKNOWN;
    } 

    // Recibir true si fallo, false si fue exito.
    return out;
}
uint8_t ClientProtocol::sendCreateLobby(const uint8_t count, std::vector<std::string>& list_maps) {
    uint8_t info[2] = {LobbyActionType::CREATE_LOBBY, count};
    protocol.sendbytes(&info, sizeof(info));
    uint8_t id_lobby = protocol.recvbyte();
    
    int count_maps = protocol.recvuint();
    list_maps.reserve(count_maps);
    list_maps.clear();
    
    while (count_maps > 0) {
        list_maps.push_back(protocol.recvmsgstr());
        count_maps--;
    }
    
    return id_lobby;
}

uint8_t ClientProtocol::recvIDSinglePlayer() {
    return protocol.recvbyte();  // id player 1
}

uint8_t ClientProtocol::recvIDDualPlayer(uint8_t* player1) {
    *player1 = protocol.recvbyte();
    return protocol.recvbyte();
}


void ClientProtocol::sendlobbyaction(const lobby_action& action) { protocol.sendbyte(action.type); }
void ClientProtocol::sendmapname(const std::string& mapname) { protocol.sendmsg(mapname); }


void ClientProtocol::recvwinconfig(int& wins_needed, int& rounds_per_set){
     wins_needed = (int) protocol.recvbyte();
     rounds_per_set = (int) protocol.recvbyte();
}

void ClientProtocol::recvmapdata(struct MapData& data) {  //, const int unit) {
    data.width = protocol.recvuint();
    data.height = protocol.recvuint();

    // Recv constant z inds.
    data.blocks_z = protocol.recvshort();
    data.boxes_z = protocol.recvshort();

    // Recv constant 'textures'/'resources'
    data.background = protocol.recvmsgstr();
    data.boxes_tex = protocol.recvmsgstr();

    // Populate textures to load.
    int count_textures = protocol.recvuint();
    data.textures.reserve(count_textures);
    data.textures.clear();
    
    while (count_textures > 0) {
        data.textures.push_back(protocol.recvmsgstr());
        count_textures--;
    }

    // Read sizes.
    int count_blocks = protocol.recvuint();
    int count_decorations = protocol.recvuint();

    data.objects.reserve(count_blocks + count_decorations);
    data.objects.clear();
    
    while (count_blocks > 0) {
        coordinate_t _x = protocol.recvuint();
        coordinate_t _y = protocol.recvuint();

        uint8_t ind_tex = protocol.recvbyte();

        data.objects.emplace_back(_x, _y  //( data.height- _y * unit) // Inverti!
                                  ,
                                  data.blocks_z, data.textures[ind_tex], ind_tex);

        count_blocks--;
    }

    while (count_decorations > 0) {
        coordinate_t _x = protocol.recvuint();
        coordinate_t _y = protocol.recvuint();
        uint8_t ind_tex = protocol.recvbyte();

        uint8_t _z = protocol.recvshort();

        data.objects.emplace_back(_x, _y  //(data.height - _y * unit)  //*unit //Inverti!
                                  ,
                                  _z, data.textures[ind_tex], ind_tex);

        count_decorations--;
    }
}

void ClientProtocol::recvstats(MatchStatsInfo& outstats) {
    outstats.numronda = protocol.recvbyte();
    outstats.champion_player = protocol.recvbyte();

    int count = protocol.recvbyte();
    outstats.stats.reserve(count);
    outstats.stats.clear();

    while (count > 0) {
        uint8_t id = protocol.recvbyte();
        uint8_t wins = protocol.recvbyte();
        outstats.stats.emplace_back(id, wins);
        count--;
    }
}

void ClientProtocol::recvlobbyplayers(std::vector<int>& players){
    int playercount = (int)protocol.recvbyte();
    players.reserve(playercount);
    while (playercount> 0) {
        players.push_back(protocol.recvbyte());
        playercount--;
    }
}


void ClientProtocol::recvplayer(PlayerDTO& player){
    player.id = protocol.recvuint();
    player.pos.x = protocol.recvuint();
    player.pos.y = protocol.recvuint();

    player.weapon = (TypeWeapon)protocol.recvbyte();
    player.move_action = (TypeMoveAction)protocol.recvbyte();

    player.doing_action = (TypeDoingAction)protocol.recvbyte();
    
    player.hp = protocol.recvbyte();
    player.munition = protocol.recvbyte();

    uint8_t packed = protocol.recvbyte();

    player.chest_armor = (bool)(packed & 1);
    packed = packed>>1;
    
    player.helmet = (bool)(packed & 1);
    packed = packed>>1;
    
    player.is_alive = (bool)(packed & 1);
    packed = packed>>1;
    
    player.aiming_up = (bool)(packed & 1);
    
}
void ClientProtocol::recvmatch(MatchDto& outstate) {
    int playercount = (int)protocol.recvbyte();

    outstate.players.reserve(playercount);
    outstate.players.clear();
    // Just in case.
    auto iterPlayer = outstate.players.begin();

    // std::cout << "CLIENT RECV PLAY COUNT" << playercount << " "<< outstate.players.size()<<
    // std::endl;

    while (playercount > 0) {
        PlayerDTO player;
        recvplayer(player);

        outstate.players.emplace(iterPlayer, player);

        ++iterPlayer;
        playercount--;
    }

    int objcount = (int)protocol.recvshort();
    // std::cout << "CLIENT RECV OBJ COUNT" << objcount << "player size? "<< outstate.players.size()
    // << std::endl;
    outstate.objects.reserve(objcount);
    outstate.objects.clear();
    
    // Objs
    while (objcount > 0) {
        DynamicObjDTO obj;

        obj.pos.x = protocol.recvuint();
        obj.pos.y = protocol.recvuint();
        obj.type = (TypeDynamicObject)protocol.recvbyte();

        outstate.objects.push_back(obj);
        objcount--;
    }

    // Game events
    int eventcount = (int)protocol.recvbyte();
    outstate.events.reserve(eventcount);
    outstate.events.clear();

    while (eventcount > 0) {
        coordinate_t x = protocol.recvuint();
        coordinate_t y = protocol.recvuint();
        GameEventType type = (GameEventType)protocol.recvbyte();
        outstate.events.emplace_back(x,y, type);
        eventcount--;
    }

    // Sounds
    eventcount = (int)protocol.recvbyte();
    outstate.sounds.reserve(eventcount);
    outstate.sounds.clear();

    while (eventcount > 0) {
        outstate.sounds.push_back((SoundEventType)protocol.recvbyte());
        eventcount--;
    }


}

bool ClientProtocol::recvstate(MatchStatsInfo& outstats, MatchDto& outstate) {

    uint8_t code = protocol.recvbyte();
    if (code == MatchStateType::INICIADA) {  // Receive matchdto
        recvmatch(outstate);
        return true;
    }
    
    outstats.state = (MatchStateType) code;
    
    if(outstats.state == MatchStateType::LOADING){
        return false; // Esta recargando el mapa! 
    }
    
    recvstats(outstats);
    return false;
}

void ClientProtocol::recvplayers(std::vector<int>& players) {
    int totalplayers = protocol.recvbyte();
    players.reserve(totalplayers);
    while (totalplayers > 0) {
        players.push_back(protocol.recvbyte());
        totalplayers--;
    }
}

// Manejo de si esta abierto o no.
bool ClientProtocol::isopen() { return protocol.isactive(); }

void ClientProtocol::close() { protocol.close(); }
