#include "event_handler.h"

EventHandler::EventHandler(ActionListener& sender, const GameContext& context,
                           SoundManager& soundManager):
        actionSender(sender), soundManager(soundManager), dualPlay(context.dualplay) {}

void EventHandler::setAction(PlayerActionDTO& action, PlayerActionType actionType, int playerId) {
    action.type = actionType;
    action.playerind = playerId;
}

void EventHandler::handleKeyDown(SDL_Keycode key, PlayerActionDTO& action) {
    switch (key) {
        case SDLK_RIGHT:
            setAction(action, MOVE_RIGHT, MAIN_PLAYER);
            break;
        case SDLK_LEFT:
            setAction(action, MOVE_LEFT, MAIN_PLAYER);
            break;
        case SDLK_DOWN:
            setAction(action, STAY_DOWN_START, MAIN_PLAYER);
            break;
        case SDLK_SPACE:
            setAction(action, JUMP, MAIN_PLAYER);
            soundManager.playSound(SoundType::JUMP);
            break;
        case SDLK_m:
            soundManager.stopBackgroundMusic();
            break;
    }

    if (dualPlay) {
        switch (key) {
            case SDLK_d:
                setAction(action, MOVE_RIGHT, SECOND_PLAYER);
                break;
            case SDLK_a:
                setAction(action, MOVE_LEFT, SECOND_PLAYER);
                break;
            case SDLK_s:
                setAction(action, STAY_DOWN_START, SECOND_PLAYER);
                break;
            case SDLK_w:
                setAction(action, JUMP, SECOND_PLAYER);
                soundManager.playSound(SoundType::JUMP);            
                break;
            case SDLK_e:
                setAction(action, SHOOT, SECOND_PLAYER);
                soundManager.playSound(SoundType::SHOT);
                break;
        }
    }
}

void EventHandler::handleKeyUp(SDL_Keycode key, PlayerActionDTO& action) {
    switch (key) {
        case SDLK_RIGHT:
            setAction(action, MOVE_RIGHT_END, MAIN_PLAYER);
            break;
        case SDLK_LEFT:
            setAction(action, MOVE_LEFT_END, MAIN_PLAYER);
            break;
        case SDLK_DOWN:
            setAction(action, STAY_DOWN_END, MAIN_PLAYER);
            break;
        case SDLK_SPACE:
            setAction(action, FLAPPING_END, MAIN_PLAYER);
            break;
    }

    if (dualPlay) {
        switch (key) {
            case SDLK_d:
                setAction(action, MOVE_RIGHT_END, SECOND_PLAYER);
                break;
            case SDLK_a:
                setAction(action, MOVE_LEFT_END, SECOND_PLAYER);
                break;
            case SDLK_s:
                setAction(action, STAY_DOWN_END, SECOND_PLAYER);
                break;
            case SDLK_w:
                setAction(action, FLAPPING_END, SECOND_PLAYER);
                break;
        }
    }
}

void EventHandler::handleExit(const SDL_Event& event, bool& isRunning_) {
    if (event.type == SDL_QUIT ||
        (event.type == SDL_KEYDOWN &&
         (event.key.keysym.sym == SDLK_q || event.key.keysym.sym == SDLK_ESCAPE))) {
        isRunning_ = false;
    }
}

void EventHandler::handle(bool& isRunning_) {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        PlayerActionDTO action;

        handleExit(event, isRunning_);
        if (!isRunning_) {
            return;

        } else if ((event.type == SDL_KEYDOWN) && (event.key.repeat == 0)) {
            handleKeyDown(event.key.keysym.sym, action);

        } else if (event.type == SDL_KEYUP) {
            handleKeyUp(event.key.keysym.sym, action);
        }

        if (action.type != NONE) {
            actionSender.doaction(action);
        }
    }
}
