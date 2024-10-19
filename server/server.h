#ifndef LIB_Server_H
#define LIB_Server_H

#include <utility>

#include "./lobbycontainer.h"
#include "./playeracceptor.h"


class Server {
protected:
    LobbyContainer lobbies;
    PlayerAcceptor acceptor;

public:
    // Delega la creacion del socket al acceptor.
    explicit Server(const char* service);

    // Asumamos por ahora que no se quiere permitir copias, ni mov.
    Server(const Server&) = delete;
    Server& operator=(const Server&) = delete;

    Server(Server&&) = delete;
    Server& operator=(Server&&) = delete;

    // Inicia el match y el acceptor. Cada uno en su thread.
    void initmatch();

    // Por si alguien quisiese saber.
    bool isrunning();

    // Cierra/termina el el match y el acceptor.
    void close();

    // Espera a que se mande la 'q'
    void waitclose();

    ~Server();
};

#endif
