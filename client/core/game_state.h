#ifndef GAME_STATE_H
#define GAME_STATE_H

class GameState {
public:
    // Checks and ends the state. Ensuring needed data
    // Is on context.
    // Returns true if should continue. False means it should exit the app.
    virtual bool endstate() = 0;


    virtual ~GameState() {}
};

#endif
