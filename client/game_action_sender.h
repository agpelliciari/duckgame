#ifndef GAME_ACTION_SENDER_H
#define GAME_ACTION_SENDER_H

#include <memory>
#include <string>

#include "client/actionlistener.h"
#include "common/clientprotocol.h"
#include "common/dtos.h"
#include "common/thread.h"

// Clase que encapsula al protocol y mantendria el estado del juego
// Proporcionado una interfaz para acciones del usuario.
class GameActionSender: private Thread, public ActionListener {
protected:
    ClientProtocol* protocol;  // cppcheck-suppress unusedStructMember

    void sendMove(char action);

public:
    void doaction(const PlayerActionDTO& action) override;
    void disconnect() override;

    // Los default sin pasar por socket/protocol.
    explicit GameActionSender(ClientProtocol& _protocol);

    GameActionSender(GameActionSender&&);
    GameActionSender& operator=(GameActionSender&&);

    // Asumamos por ahora que no se quiere permitir copias, ni mov.
    GameActionSender(const GameActionSender&) = delete;
    GameActionSender& operator=(const GameActionSender&) = delete;


    bool isrunning();

    // void startJoinLobby(uint8_t playercount, unsigned int idlobby);
    // void startCreateLobby(uint8_t playercount);

    void run() override;

    int getcount();
    ~GameActionSender();
};

#endif
