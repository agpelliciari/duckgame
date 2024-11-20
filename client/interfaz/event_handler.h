#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

#include <SDL2/SDL.h>

#include "client/actionlistener.h"
#include "client/gamecontext.h"
#include "common/dtosplayer.h"

#include "sound_manager.h"

#define MAIN_PLAYER 0
#define SECOND_PLAYER 1

class EventHandler {
private:
    ActionListener& actionSender;

    SoundManager& soundManager;

    bool dualPlay;  // cppcheck-suppress unusedStructMember

    void setAction(PlayerActionDTO& action, PlayerActionType actionType, int playerId);

    void handleKeyDown(SDL_Keycode key, PlayerActionDTO& action);

    void handleKeyUp(SDL_Keycode key, PlayerActionDTO& action);

    void handleExit(const SDL_Event& event, bool& isRunning_);

public:
    EventHandler(ActionListener& sender, const GameContext& context, SoundManager& soundManager);

    // Keyboard Event processing
    void handle(bool& isRunning_);
};

#endif
