#include "event_handler.h"

EventHandler::EventHandler(ActionListener& sender, const GameContext& context):
        actionSender(sender), dualPlay(context.dualplay) {}

void EventHandler::handle(bool& isRunning_) {
    SDL_Event event;
    PlayerActionDTO action;

    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            isRunning_ = false;
            return;
        } else if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
                case SDLK_RIGHT:
                    action.type = MOVE_RIGHT;
                    break;
                case SDLK_LEFT:
                    action.type = MOVE_LEFT;
                    break;
                case SDLK_DOWN:
                    action.type = STAY_DOWN;
                    break;
                case SDLK_SPACE:
                    action.type = JUMP;
                    break;
                case SDLK_ESCAPE:
                case SDLK_q:
                    isRunning_ = false;
                    return;

                    if (dualPlay) {
                        case SDLK_d:
                            action.type = MOVE_RIGHT;
                            action.playerind = 1;
                            break;
                        case SDLK_a:
                            action.type = MOVE_LEFT;
                            action.playerind = 1;
                            break;
                        case SDLK_s:
                            action.type = STAY_DOWN;
                            action.playerind = 1;
                            break;
                        case SDLK_w:
                            action.type = JUMP;
                            action.playerind = 1;
                            break;
                    }
            }
        } else if (event.type == SDL_KEYUP) {
            action.type = NONE;
            if ((event.key.keysym.sym == SDLK_a) || (event.key.keysym.sym == SDLK_d) ||
                (event.key.keysym.sym == SDLK_w) || (event.key.keysym.sym == SDLK_s)) {
                action.playerind = 1;
            }
        }

        actionSender.doaction(action);
    }
}
