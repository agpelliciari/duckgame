#ifndef SIMPLE_MESSENGER
#define SIMPLE_MESSENGER

#include <cstdint>
#include <string>
#include <vector>

#include "common/core/messenger.h"

class SimpleMessenger: public Messenger {
private:
    std::vector<char> buffer;  // cppcheck-suppress unusedStructMember


    bool closed;     // cppcheck-suppress unusedStructMember
    bool canexpand;  // cppcheck-suppress unusedStructMember
    int cap;        // cppcheck-suppress unusedStructMember

    int offsetRead;   // cppcheck-suppress unusedStructMember
    int offsetWrite;  // cppcheck-suppress unusedStructMember

    // Enviar/Recibir la cantidad especificada, dentro del size especificado.
    int sendsome(const void* data, unsigned int sz);
    unsigned int recvsome(void* data, unsigned int sz);

    void chktOpen() const;

public:
    SimpleMessenger(int size, bool _canexpand);
    
    // Metodos utilitarios para hacer de como si fuera un builder/ pre envio por socket.
    int size() const;
    const char * first() const;


    void seek(int offset);  // Setea el offset del read.
    void reset();           // Resetea 'borra' toda la informacion. Setea ambos offsets a 0.


    // Intenta enviar todo y devuelve lo que envio/ tira excepcion
    unsigned int trysendall(const void* data, unsigned int sz) override;
    void sendall(const void* data, unsigned int sz) override;

    // Intenta leer lo maximo que pueda, a lo sumo sz. Retorna la cantidad leida.
    unsigned int tryrecvall(void* data, unsigned int sz) override;
    // Intenta leer sz bytes. Tira excepcion sino lee todo.
    void recvall(void* data, unsigned int sz) override;

    // Cierra parcial o completamente. Es no except. Devuelve -1 si fallo.
    int finish() override;

    // Destructor, se encarga de llamar al shutdown si no lo fue.
    ~SimpleMessenger();
};

#endif
