#ifndef MESSENGER_H
#define MESSENGER_H


// Clase/interfaz base para hacer las cosas testeables/mockeables
// Y no solo eso capaz permitir hacer el juego en base a otros tipos
// de comunicacion/sockets.
class Messenger {
public:
    // Enviar la cantidad especificada, pero puede que mande/reciba menos.
    virtual int sendsome(const void* data, unsigned int sz) = 0;
    virtual unsigned int recvsome(void* data, unsigned int sz) = 0;


    // Intenta enviar todo y devuelve lo que envio/ tira excepcion
    virtual unsigned int trysendall(const void* data, unsigned int sz) = 0;
    virtual void sendall(const void* data, unsigned int sz) = 0;

    // Intenta leer lo maximo que pueda, a lo sumo sz. Retorna la cantidad leida.
    virtual unsigned int tryrecvall(void* data, unsigned int sz) = 0;

    // Intenta leer sz bytes. Tira excepcion sino lee todo.
    virtual void recvall(void* data, unsigned int sz) = 0;

    // Cierra parcial o completamente. Es no except. Devuelve -1 si fallo.
    virtual int shutdown(int how) = 0;

    // Cierra el socket. Aunque no necesariamente haria el shutdown.
    virtual int close() = 0;

    // Destructor, se encarga de llamar al shutdown si no lo fue.
    virtual ~Messenger() {}
};
#endif
