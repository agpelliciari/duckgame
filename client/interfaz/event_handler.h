#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

#include <SDL2/SDL.h>

#include "client/actionlistener.h"
#include "client/gamecontext.h"
#include "common/dtosplayer.h"

class EventHandler {
private:
    ActionListener& actionSender;

    bool dualPlay;  // cppcheck-suppress unusedStructMember

public:
    EventHandler(ActionListener& sender, const GameContext& context);

    // Event processing:
    // - If window is closed, or Q or Escape buttons are pressed, quit the
    // application
    // - If Right key is pressed, character would run
    // - If Right key is released, character would stop
    // - If Space key is pressed, character would jump
    // - If Down key is pressed, character would lay dead
    void handle(bool& isRunning_);
};

#endif
