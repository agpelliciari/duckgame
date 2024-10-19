#ifndef LIB_LOBBY_H
#define LIB_LOBBY_H

#include <mutex>
#include <condition_variable>

#include <queue>
#include <utility>

#include "./match.h"

typedef unsigned int lobbyID;

// Clase para encapsular la logica de lopeado. De forma asincrona.
// Delega el manejo del estado, notificado de eventos y recepcion de acciones
class Lobby{
private:
    lobbyID id; // cppcheck-suppress unusedStructMember
    PlayerContainer players;
    Match match;
    std::condition_variable match_started;
public:
    // Se tendra composicion con un unico observer de eventos al match.
    explicit Lobby(lobbyID _id);

    // Asumamos por ahora que no se quiere permitir copias, ni mov.
    Lobby(const Lobby&) = delete;
    Lobby& operator=(const Lobby&) = delete;

    Lobby(Lobby&&) = delete;
    Lobby& operator=(Lobby&&) = delete;
    
    lobbyID getID() const;
    
    bool operator==(const Lobby& other) const;
  
  
    // En la lobby se agregan jugadores. Y podrian irse tambien.
    void addPlayer(Player* player);
    
    Match& waitStart(std::unique_lock<std::mutex>& lock);
    // Inicia la partida.. y notifica a los que esperan.
    Match& start();
    bool isrunning();

    // Libera, bien podria prescindirse y usar un destructor.
    void finish();
    
    ~Lobby();
};

#endif
