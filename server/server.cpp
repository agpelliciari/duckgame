#include "./server.h"

#include <iostream>

static const char EXIT_SIGN = 'q';

// Se entiende es mas ajustado a lo que se pidio.
// El match y acceptor son miembros para denotar que el service/socket es usable solo una vez.
Server::Server(const char* service): lobbies(), acceptor(service, lobbies) {}


// Inicia el match y tambien el acceptor en si.
void Server::initmatch() {
    // Se inicia sin esperar a algun player.
    // match.init();
    acceptor.init();
}

bool Server::isrunning() { return acceptor.isrunning(); }

void Server::waitclose() {
    std::string out;

    while (isrunning() && std::cin >> out) {
        if (out.length() == 1 && *(out.data()) == EXIT_SIGN) {
            std::cout << "Pressed 'q' ... should close server\n";
            break;
        } else{
            std::cout << "Stdin: '"<< out <<"' not 'q'!\n";
        }
    }
    // Se deja el close para despues el close.. o para el destructor.
}

void Server::close() {
    // Mejor hacer las cosas explicitas.
    // Ya que podria haber problemas si el match se destruye primero y se invalida la referencia.
    std::cout << "----Finishing server acceptor\n";
    acceptor.finish();
    std::cout << "----Finishing server lobbies \n";
    lobbies.finishAll();
}
Server::~Server() { close(); }
