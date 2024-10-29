#include "loop_ui.h"

UILoop::UILoop(ActionListener& dtoSender, SimpleEventListener& _events,
               const GameContext& gameContext):
        sdlLib(SDL_INIT_VIDEO),
        window("UILOOP demo", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
               SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE),
        renderer(window, -1, SDL_RENDERER_ACCELERATED),
        textures(renderer),
        animation(gameContext),
        sender(dtoSender),
        matchDtoQueue(_events),
        lastUpdate(),
        context(gameContext),
        isRunning_(true) {}

void UILoop::exec() {
    try {
        while (isRunning_) {
            unsigned int frameStart = SDL_GetTicks();

            handleEvent();

            update();

            draw();

            frameDelay(frameStart);
        }
    } catch (const std::exception& e) {
        std::cerr << "Exception caught in UILoop::exec: " << e.what() << std::endl;
        isRunning_ = false;
    } catch (...) {
        std::cerr << "Unknown exception caught in UILoop::exec" << std::endl;
        isRunning_ = false;
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

                    if (context.dualplay) {
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
        }  // else if (event.type == SDL_KEYUP) {   //! chequear desp si es necesario
           // action.type = NONE;
           // action.playerind = (event.key.keysym.sym == SDLK_d || event.key.keysym.sym == SDLK_a
           // ||
           //                   event.key.keysym.sym == SDLK_s || event.key.keysym.sym == SDLK_w) ?
           //                        1 :
           //                      0;
        //}

        sender.doaction(action);
    }
}

void UILoop::update() {

    MatchDto matchUpdate;

    if (matchDtoQueue.try_update(matchUpdate)) {
        lastUpdate = matchUpdate;
        if (matchUpdate.info.estado == TERMINADA) {
            isRunning_ = false;
        }
    }

    animation.updateFrame();

    animation.updateSprite(matchUpdate);
}

void UILoop::draw() {
    // Clear screen
    renderer.SetDrawColor(255, 255, 255, 255);  // White background
    renderer.Clear();

    // Draw ground
    renderer.SetDrawColor(0, 0, 0, 255);  // Black color
    renderer.DrawLine(0, GROUND_Y, SCREEN_WIDTH, GROUND_Y);

    for (const PlayerDTO& player: lastUpdate.players) {
        drawPlayer(player);
    }

    // Show rendered frame
    renderer.Present();
}

void UILoop::drawPlayer(const PlayerDTO& player) {
    // Determine the flip mode based on the last direction
    SDL_RendererFlip flip = animation.isFacingLeft(player.id) ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;

    // Draw player sprite
    renderer.Copy(textures.getTexture(player.id - 1),
                  SDL2pp::Rect(animation.getSpriteY(player.id), animation.getSpriteX(player.id),
                               SPRITE_WIDTH, SPRITE_HEIGHT),
                  SDL2pp::Rect(player.coord_x, player.coord_y, 50, 50), 0.0, SDL2pp::Point(0, 0),
                  flip);
}

void UILoop::frameDelay(unsigned int frameStart) {
    unsigned int frameTime = SDL_GetTicks() - frameStart;
    if (FRAME_DELAY > frameTime) {
        SDL_Delay(FRAME_DELAY - frameTime);
    }
}

UILoop::~UILoop() = default;
