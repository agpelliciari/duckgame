#ifndef LIB_MatchAcceptor_H
#define LIB_MatchAcceptor_H

#include <list>

#include "../common_src/socket.h"
#include "../common_src/thread.h"
#include "./match.h"
#include "./playercontroller.h"

// Clase para guardar nuevos controllers, pertenecientes a un match.
// Personalmente... no se considera que esta clase perse deba tener el ownership
// del socket. Pero entiendo es lo que se queria. Dado esto. Este acceptor tambien hereda thread.
// Definiendo el loopeado para recibir a los nuevos players.
class MatchAcceptor: private Thread {
public:
    typedef std::list<PlayerController> controller_list;

private:
    // Se guarda el socket del server. Para ir generando los controllers.
    Socket sktacceptor;


    // No es realmente necesario. Pero tambien ayuda a los logs.

    player_id last_player;  // cppcheck-suppress unusedStructMember


    Match& match;                 // cppcheck-suppress unusedStructMember
    controller_list controllers;  // cppcheck-suppress unusedStructMember

    // No expone esta logica al exterior al tener ahora el ownership del skt
    // Agrega un nuevo jugador. A partir del socket.
    void newPlayer(Socket&& connection);

    // Limpia el aceptador de controllers desconectados.
    void cleanself();

    // Desconecta/termina a todo jugador conectado.
    void disconnectAll();

public:
    explicit MatchAcceptor(const char* service, Match& _match);

    // No copy nor mov.
    MatchAcceptor(const MatchAcceptor&) = delete;
    MatchAcceptor& operator=(const MatchAcceptor&) = delete;

    MatchAcceptor(MatchAcceptor&&) = delete;
    MatchAcceptor& operator=(MatchAcceptor&&) = delete;


    // Como pre condicion esta que el server siga abierto.
    // Intenta empezar el match. Los va a esperar en este thread
    // y empieza thread para el match. El acceptor tambien inicia los
    // de los players.
    void run() override;


    // Metodos sobre escritos para extender medianamente los del thread.
    void init();

    void finish();
    ~MatchAcceptor();
};

#endif
