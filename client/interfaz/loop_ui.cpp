#include "loop_ui.h"

UILoop::UILoop(ActionListener& dtoSender, SimpleEventListener& _events, bool twoPlayersFlag):
        sdlLib(SDL_INIT_VIDEO),
        window("UILOOP demo", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
               SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE),
        renderer(window, -1, SDL_RENDERER_ACCELERATED),
        textures(renderer),
        animation(),
        sender(dtoSender),
        dto_events(_events),
        isRunning_(true),
        twoPlayers_(twoPlayersFlag) {}

void UILoop::exec() {
    while (isRunning_) {
        unsigned int frameStart = SDL_GetTicks();

        handleEvent();

        update();

        draw();

        frameDelay(frameStart);
    }
}

void UILoop::handleEvent() {
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

                    if (twoPlayers_) {
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
            action.playerind = (event.key.keysym.sym == SDLK_d || event.key.keysym.sym == SDLK_a ||
                                event.key.keysym.sym == SDLK_s || event.key.keysym.sym == SDLK_w) ?
                                       1 :
                                       0;
        }
        sender.doaction(action);
    }
}

void UILoop::update() {

    animation.updateFrame();

    animation.updatePosition();

    animation.updateSprite();
}

void UILoop::draw() {
    // Clear screen
    renderer.SetDrawColor(255, 255, 255, 255);  // White background
    renderer.Clear();

    // Draw ground
    renderer.SetDrawColor(0, 0, 0, 255);  // Black color
    renderer.DrawLine(0, GROUND_Y, SCREEN_WIDTH, GROUND_Y);

    // Determine the flip mode based on the last direction
    SDL_RendererFlip flip = animation.isFacingLeft() ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;

    // Draw player sprite
    renderer.Copy(textures.getTexture(YELLOW_DUCK_SPRITE),
                  SDL2pp::Rect(animation.getSpriteX(), animation.getSpriteY(), SPRITE_WIDTH,
                               SPRITE_HEIGHT),
                  SDL2pp::Rect(static_cast<int>(animation.getPositionX()) - 25,
                               static_cast<int>(animation.getPositionY()) - 44, 50,
                               50),  // Nuevo rectangulo, se expande event sprite
                  0.0, SDL2pp::Point(0, 0), flip);

    // Show rendered frame
    renderer.Present();
}

void UILoop::frameDelay(unsigned int frameStart) {
    unsigned int frameTime = SDL_GetTicks() - frameStart;
    if (FRAME_DELAY > frameTime) {
        SDL_Delay(FRAME_DELAY - frameTime);
    }
}

UILoop::~UILoop() = default;
