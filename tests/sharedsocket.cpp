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

// Cierra parcial o completamente. Es no except. Devuelve -1 si fallo.
int SharedSocket::shutdown(int how) { return messenger.shutdown(how); }

// Cierra el socket. Aunque no necesariamente haria el shutdown.
int SharedSocket::close() { return messenger.close(); }


// Destructor, se encarga de llamar al shutdown si no lo fue.
SharedSocket::~SharedSocket() {}
