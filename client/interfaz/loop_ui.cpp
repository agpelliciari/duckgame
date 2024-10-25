#include "loop_ui.h"

UILoop::UILoop():
        sdlLib(SDL_INIT_VIDEO),
        window("UILOOP demo", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
               SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE),
        renderer(window, -1, SDL_RENDERER_ACCELERATED),
        sprites(renderer, DATA_PATH "/yellow_duck.png"),
        is_running_(true),
        animation() {}

void UILoop::exec() {
    while (is_running_) {
        unsigned int frameStart = SDL_GetTicks();

        handleEvent();

        update();

        draw();

        frameDelay(frameStart);
    }
}

void UILoop::handleEvent() {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            is_running_ = false;
        } else if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
                case SDLK_RIGHT:
                    animation.rightCommandFlags();
                    break;
                case SDLK_LEFT:
                    animation.leftCommandFlags();
                    break;
                case SDLK_DOWN:
                    animation.downCommandFlags();
                    break;
                case SDLK_SPACE:
                    animation.spaceCommandFlags();
                    break;
                case SDLK_ESCAPE:
                case SDLK_q:
                    is_running_ = false;
                    break;
            }
        } else if (event.type == SDL_KEYUP) {
            switch (event.key.keysym.sym) {
                case SDLK_RIGHT:
                    animation.stopRightCommand();
                    break;
                case SDLK_LEFT:
                    animation.stopLeftCommand();
                    break;
                case SDLK_DOWN:
                    animation.stopDownCommand();
                    break;
                case SDLK_SPACE:
                    animation.stopSpaceCommand();
                    break;
            }
        }
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
    renderer.Copy(sprites,
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
