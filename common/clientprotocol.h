#ifndef LIB_ClientProtocol_H
#define LIB_ClientProtocol_H

#define BUFF_LEN_CLIENT 128


#include <atomic>
#include <string>
#include <utility>
#include <vector>

#include "./dtosobject.h"
#include "common/core/protocol.h"
#include "common/dtosgame.h"
#include "common/dtoslobby.h"

// Mas que MapObject, DrawableObject.
struct MapObject {
    int row;
    int column;
    int zIndex;

    const std::string& texture;
    uint16_t ind_texture;

    MapObject(const int x, const int y, const uint16_t z, const std::string& tex,
              const uint16_t ind):
            row(y), column(x), zIndex(z), texture(tex), ind_texture(ind) {}
};

struct MapData {
    int width;   // cppcheck-suppress unusedStructMember
    int height;  // cppcheck-suppress unusedStructMember

    uint16_t blocks_z;  // cppcheck-suppress unusedStructMember
    uint16_t boxes_z;   // cppcheck-suppress unusedStructMember

    std::string background;  // cppcheck-suppress unusedStructMember
    std::string boxes_tex;   // cppcheck-suppress unusedStructMember

    std::vector<std::string> textures;      // cppcheck-suppress unusedStructMember
    std::vector<struct MapObject> objects;  // cppcheck-suppress unusedStructMember

    MapData(): width(0), height(0), blocks_z(0), boxes_z(0) {}
};


// Extension del protocolo base a usar.
class ClientProtocol {

protected:
    Protocol protocol;  // Composicion con el protocolo base para la conexion
public:
    // El default a partir de la abstraccion de socket
    explicit ClientProtocol(Messenger& connection);

    // Para mayor facilidad... el move del client protocol permite mas facil
    // reiniciar una conexion.
    ClientProtocol(ClientProtocol&&) = delete;
    ClientProtocol& operator=(ClientProtocol&&) = delete;

    // Asumamos por ahora que no se quiere permitir copias
    ClientProtocol(const ClientProtocol&) = delete;
    ClientProtocol& operator=(const ClientProtocol&) = delete;

    lobby_info sendJoinLobby(const uint8_t id_match, const uint8_t count);
    uint8_t sendCreateLobby(const uint8_t count);

    uint8_t recvIDSinglePlayer();
    uint8_t recvIDDualPlayer(uint8_t* player1);


    void recvlobbyinfo(lobby_info& out);

    void sendlobbyaction(const lobby_action& action);
    void sendmapname(const std::string& mapname);

    void sendaction(PlayerActionDTO& action);

    MatchDto recvstate();

    void recvmapdata(struct MapData& data, const int unit);

    bool isopen();
    void close();
};

#endif
