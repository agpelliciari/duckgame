#ifndef Lobby_STATE_H
#define Lobby_STATE_H

// Clase que encapsula al protocol y mantendria el estado del juego
// Proporcionado una interfaz para acciones del usuario.
class GameState {
public:
    // Checks and ends the state. Ensuring needed data
    // Is on context.
    // Returns true if should continue. False means it should exit the app.
    virtual bool endstate() = 0;


    virtual ~GameState() {}
};

#endif
