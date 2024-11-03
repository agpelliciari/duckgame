#ifndef MOCK_SHARED_SOCKET
#define MOCK_SHARED_SOCKET

#include <cstdint>
#include <string>

#include "common/core/messenger.h"

class SharedSocket: public Messenger {
private:
    Messenger& messenger;

public:
    explicit SharedSocket(Messenger& realsocket);

    // Intenta enviar todo y devuelve lo que envio/ tira excepcion
    unsigned int trysendall(const void* data, unsigned int sz) override;
    void sendall(const void* data, unsigned int sz) override;

    // Intenta leer lo maximo que pueda, a lo sumo sz. Retorna la cantidad leida.
    unsigned int tryrecvall(void* data, unsigned int sz) override;
    // Intenta leer sz bytes. Tira excepcion sino lee todo.
    void recvall(void* data, unsigned int sz) override;

    // Cierra el socket
    int finish() override;

    // Destructor, se encarga de llamar al shutdown si no lo fue.
    ~SharedSocket();
};

#endif
