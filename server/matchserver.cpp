#include "./matchserver.h"

#include <iostream>

static const char EXIT_SIGN = 'q';

// Se entiende es mas ajustado a lo que se pidio.
// El match y acceptor son miembros para denotar que el service/socket es usable solo una vez.
MatchServer::MatchServer(const char* service): lobbies(), acceptor(service, lobbies) {}


// Inicia el match y tambien el acceptor en si.
void MatchServer::initmatch() {
    // Se inicia sin esperar a algun player.
    //match.init();
    acceptor.init();
}

bool MatchServer::isrunning() { return acceptor.isrunning(); }

void MatchServer::waitclose() {
    std::string out;

    while (isrunning() && std::cin >> out) {
        if (out.length() == 1 && *(out.data()) == EXIT_SIGN) {
            break;
        }
    }
    // Se deja el close para despues el close.. o para el destructor.
}

void MatchServer::close() {
    // Mejor hacer las cosas explicitas.
    // Ya que podria haber problemas si el match se destruye primero y se invalida la referencia.
    acceptor.finish();
    lobbies.finishAll();
}
MatchServer::~MatchServer() { close(); }
