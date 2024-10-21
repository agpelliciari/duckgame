#ifndef LIB_PlayerAcceptor_H
#define LIB_PlayerAcceptor_H

#include <list>

#include "./controlreceiver.h"
#include "./lobbycontainer.h"
#include "common/core/socket.h"
#include "common/thread.h"

// Clase para guardar nuevos controllers, pertenecientes a un match.
// Personalmente... no se considera que esta clase perse deba tener el ownership
// del socket. Pero entiendo es lo que se queria. Dado esto. Este acceptor tambien hereda thread.
// Definiendo el loopeado para recibir a los nuevos players.
class PlayerAcceptor: private Thread {
public:
    typedef std::list<ControlReceiver> controller_list;

private:
    // Se guarda el socket del server. Para ir generando los controllers.
    Socket sktacceptor;

    LobbyContainer& lobbies;      // cppcheck-suppress unusedStructMember
    controller_list controllers;  // cppcheck-suppress unusedStructMember

    // No expone esta logica al exterior al tener ahora el ownership del skt
    // Agrega un nuevo jugador. A partir del socket.
    void newPlayer(Socket&& connection);

    // Limpia el aceptador de controllers desconectados.
    void cleanself();

    // Desconecta/termina a todo jugador conectado.
    void disconnectAll();

public:
    explicit PlayerAcceptor(const char* service, LobbyContainer& _lobbies);

    // No copy nor mov.
    PlayerAcceptor(const PlayerAcceptor&) = delete;
    PlayerAcceptor& operator=(const PlayerAcceptor&) = delete;

    PlayerAcceptor(PlayerAcceptor&&) = delete;
    PlayerAcceptor& operator=(PlayerAcceptor&&) = delete;


    // Como pre condicion esta que el server siga abierto.
    // Intenta empezar el match. Los va a esperar en este thread
    // y empieza thread para el match. El acceptor tambien inicia los
    // de los players.
    void run() override;


    // Metodos sobre escritos para extender medianamente los del thread.
    void init();
    bool isrunning();

    void finish();
    ~PlayerAcceptor();
};

#endif
