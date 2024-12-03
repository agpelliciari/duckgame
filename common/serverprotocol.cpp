#include "./serverprotocol.h"

#include <iostream>
#include <string>
#include <utility>

//#include "./gameerror.h"
#include "common/protocolerror.h"
#include "common/core/simplemessenger.h"

// ServerProtocol::ServerProtocol(Socket& messenger): Protocol(messenger) {}
ServerProtocol::ServerProtocol(Messenger& messenger): Protocol(messenger) {}

uint8_t ServerProtocol::recvplayercount() { return this->recvbyte(); }

LobbyActionType ServerProtocol::recvlobbyaction() {
    uint8_t sign;
    if (this->tryrecvbyte(&sign)) {
        return (LobbyActionType)sign;  // Podria fallar el casteo? la verificacion es posterior.
    }

    throw ProtocolError("Did not receive a lobby action");
}
std::string ServerProtocol::recvmapname() { return this->recvmsgstr(); }


void ServerProtocol::notifyaction(const LobbyResponseType response) { this->sendbyte(response); }

void ServerProtocol::notifyinfo(const LobbyResponseType response, const uint8_t data) {
    uint8_t bytes[2] = {response, data};
    this->sendbytes(&bytes, 2);
}
void ServerProtocol::notifyevent(const lobby_info& info) {
    uint8_t bytes[2] = {info.action, info.data};
    this->sendbytes(&bytes, 2);
}

uint8_t ServerProtocol::recvlobbyid() { return this->recvbyte(); }

LobbyActionType ServerProtocol::recvresolveinfo() {
    uint8_t sign;
    if (!this->tryrecvbyte(&sign)) {
        throw ProtocolError("Did not receive lobby resolve info.");
    }
    if (LobbyActionType::CREATE_LOBBY == sign) {
        return CREATE_LOBBY;
    }

    if (LobbyActionType::JOIN_LOBBY == sign) {
        return JOIN_LOBBY;
    }

    throw ProtocolError("Invalid lobby resolve action!");
}

void ServerProtocol::notifyid(uint8_t id) { this->sendbyte(id); }


PlayerActionDTO ServerProtocol::recvaction() {
    PlayerActionDTO action;
    if (!this->tryrecvbytes(&action, sizeof(action))) {
        active = false;
        throw ProtocolError("Did not receive action!");
    }

    // std::cout << "Receiving action from: " << (int)action.playerind << "= " << (int)action.type
    //<< std::endl;

    return action;
}


// Garantiza que sea un state de estadistica.
#define stat_state(vl) (vl == INICIADA? MatchStateType::ROUND_END: vl) 
void ServerProtocol::sendstats(const MatchStatsInfo& state) {
    std::cout << "Sending stats!! " << state.parse() << std::endl;

    uint8_t general[3] = {(uint8_t)stat_state(state.state), (uint8_t)state.numronda, state.champion_player};    
    
    this->sendbytes(general, sizeof(general));

    this->sendbyte(state.stats.size());

    for (const PlayerStatDto& stat: state.stats) {
        this->sendbyte(stat.id);
        this->sendbyte(stat.wins);
    }
}


void ServerProtocol::sendstate(const MatchDto&& state) { sendstate(state); }

void ServerProtocol::sendstate(const MatchDto& state) {

    // std::cout << "SENDING STATE DTO!\n";
    this->sendbyte((uint8_t)MatchStateType::INICIADA);
    
    // Un msg builder basicamente.
    
    SimpleMessenger auxmsg(128, true);
    Protocol auxprot(auxmsg);
    
    // Envio de players.
    auxprot.sendbyte(state.players.size());
    for (const PlayerDTO& player: state.players) {
        sendplayer(auxprot, player);
    }
    this->sendbytes(auxmsg.first(), auxmsg.size());    
    auxmsg.reset(); // Reset tras envio del mensaje.


    auxprot.sendshort(state.objects.size());
    for (const DynamicObjDTO& obj: state.objects) {
        auxprot.senduint(obj.pos.x);
        auxprot.senduint(obj.pos.y);
        auxprot.sendbyte((uint8_t)obj.type);
    }
    
    this->sendbytes(auxmsg.first(), auxmsg.size());    
    auxmsg.reset(); // Reset tras envio del mensaje.
    

    auxprot.sendbyte(state.events.size());

    for (const GameEvent& event: state.events) {
        auxprot.senduint(event.pos.x);
        auxprot.senduint(event.pos.y);
        auxprot.sendbyte((uint8_t)event.type);
    }
    
    this->sendbytes(auxmsg.first(), auxmsg.size());    
    auxmsg.reset(); // Reset tras envio del mensaje.
    
    
    // No hace falta usar por ahora ya que son uint8_t
    this->sendbyte(state.sounds.size());
    this->sendbytes(state.sounds.data(),
                    state.sounds.size());

}

void ServerProtocol::sendwinconfig(const int wins_needed,const int rounds_per_set){
    uint8_t info[2] = {(uint8_t)wins_needed,(uint8_t) rounds_per_set};
    this->sendbytes(&info[0],2);
}

// Para mayor flexibilidad.. por ahora.
void ServerProtocol::sendplayer(Protocol& protocol, const PlayerDTO& player) {

    protocol.senduint(player.id);
    protocol.senduint(player.pos.x);
    protocol.senduint(player.pos.y);
    
    protocol.sendbyte((uint8_t)player.weapon);
    protocol.sendbyte((uint8_t)player.move_action);
    protocol.sendbyte((uint8_t)player.doing_action);
    protocol.sendbyte((uint8_t)player.hp);
    protocol.sendbyte((uint8_t)player.munition);
    
    // Al user un builder temporal en memoria. No hace falta. optimizar a mandar 1 send.
    
    // Pack things.    
    uint8_t res = (uint8_t)player.aiming_up;
    
    res = res<<1 | (uint8_t)player.is_alive;
    res = res<<1 | (uint8_t)player.helmet;
    res = res<<1 | (uint8_t)player.chest_armor;
    
    protocol.sendbyte(res);
}


void ServerProtocol::sendmaplist(const std::vector<std::string>& maps){
    this->senduint(maps.size());
    for(const std::string& map: maps){
         this->sendmsg(map);
    }
}

void ServerProtocol::resendmapinfo(const MapInfo& map){ // If resend is needed!
    this->sendbyte((uint8_t)MatchStateType::LOADING);    
    sendmapinfo(map);
}
void ServerProtocol::sendmapinfo(const MapInfo& map) {

    // Send Map size
    this->senduint(map.size.x);
    this->senduint(map.size.y);

    // Send constant z inds
    this->sendshort(map.blocks_z);
    this->sendshort(map.boxes_z);

    // Send constant 'textures'/'resources'
    this->sendmsg(map.background);
    this->sendmsg(map.boxes_tex);

    // Send textures.
    this->senduint(map.textures.size());
    for (const std::string& tex: map.textures) {
        this->sendmsg(tex);
    }

    // Send objects sizes.
    this->senduint(map.blocks.size());
    this->senduint(map.decorations.size());

    // Send blocks
    for (const BlockDTO& block: map.blocks) {
        this->senduint(block.pos.x);
        this->senduint(block.pos.y);
        this->sendbyte(block.texture_id);
    }

    // Send decorations
    for (const DecorationDTO& decoration: map.decorations) {
        this->senduint(decoration.pos.x);
        this->senduint(decoration.pos.y);
        this->sendbyte(decoration.texture_id);

        this->sendshort(decoration.z_ind);
    }
}


// bool ServerProtocol::isopen() { return this->isactive(); }

// void ServerProtocol::close() { this->close(); }


    //uint8_t info[5] = {
    //     (uint8_t)player.weapon,
    //     (uint8_t)player.move_action,
    //     (uint8_t)player.doing_action,
    //     (uint8_t)player.hp,
    //     (uint8_t)player.munition
    //};    
    //this->sendbytes(&info[0], 5);

