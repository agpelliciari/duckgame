#ifndef LIB_MatchServer_H
#define LIB_MatchServer_H

#include <utility>

#include "./lobbycontainer.h"
#include "./playeracceptor.h"


class MatchServer {
protected:
    LobbyContainer lobbies;
    PlayerAcceptor acceptor;

public:
    // Delega la creacion del socket al acceptor.
    explicit MatchServer(const char* service);

    // Asumamos por ahora que no se quiere permitir copias, ni mov.
    MatchServer(const MatchServer&) = delete;
    MatchServer& operator=(const MatchServer&) = delete;

    MatchServer(MatchServer&&) = delete;
    MatchServer& operator=(MatchServer&&) = delete;

    // Inicia el match y el acceptor. Cada uno en su thread.
    void initmatch();

    // Por si alguien quisiese saber.
    bool isrunning();

    // Cierra/termina el el match y el acceptor.
    void close();

    // Espera a que se mande la 'q'
    void waitclose();

    ~MatchServer();
};

#endif
