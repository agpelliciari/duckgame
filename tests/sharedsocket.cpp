#include "./sharedsocket.h"

SharedSocket::SharedSocket(Messenger& realsocket): messenger(realsocket) {}

// Intenta enviar todo y devuelve lo que envio/ tira excepcion
unsigned int SharedSocket::trysendall(const void* data, unsigned int sz) {
    return messenger.trysendall(data, sz);
}
void SharedSocket::sendall(const void* data, unsigned int sz) { messenger.sendall(data, sz); }

// Intenta leer lo maximo que pueda, a lo sumo sz. Retorna la cantidad leida.
unsigned int SharedSocket::tryrecvall(void* data, unsigned int sz) {
    return messenger.tryrecvall(data, sz);
}
// Intenta leer sz bytes. Tira excepcion sino lee todo.
void SharedSocket::recvall(void* data, unsigned int sz) { messenger.recvall(data, sz); }

// Cierra el socket.
int SharedSocket::finish() { return messenger.finish(); }


// Destructor, se encarga de llamar al shutdown si no lo fue.
SharedSocket::~SharedSocket() {}
