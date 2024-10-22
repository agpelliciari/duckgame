#ifndef LIB_Client_H
#define LIB_Client_H

#include <string>
#include <memory>

#include "common/clientprotocol.h"
#include "common/core/socket.h"
#include "common/thread.h"


#include "./lobbymode.h"
#include "./joinlobbymode.h"
#include "./lobbycreatemode.h"

// Clase que encapsula al protocol y mantendria el estado del juego
// Proporcionado una interfaz para acciones del usuario.
class Client : private Thread{
protected:
    ClientProtocol protocol;
    bool isJoining;
    std::unique_ptr<LobbyMode> mode;    
    
    unsigned int inputnum();

    void sendMove(char action);
public:
    // Los default sin pasar por socket/protocol.
    explicit Client(const char* host, const char* service);
    explicit Client(const char* service);
    // Permitamos el mov desde uno existente para mayor flexibilidad?
    explicit Client(Protocol&& prot);

    // Asumamos por ahora que no se quiere permitir copias, ni mov.
    Client(const Client&) = delete;
    Client& operator=(const Client&) = delete;

    Client(Client&&) = delete;
    Client& operator=(Client&&) = delete;
    
    
    bool isrunning();
    
    JoinLobbyMode& startJoinLobby(uint8_t playercount, unsigned int idlobby);
    LobbyCreateMode& startCreateLobby(uint8_t playercount);
    
    void run() override;
    
    
    int getcount();
    ~Client();

};

#endif
