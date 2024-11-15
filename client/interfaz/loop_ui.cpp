#include "loop_ui.h"

UILoop::UILoop(ActionListener& dtoSender, SimpleEventListener& _events,
               const GameContext& gameContext):
        sdlLib(SDL_INIT_VIDEO | SDL_INIT_AUDIO),
        window("DuckGame", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, INITIAL_SCREEN_WIDTH,
               INITIAL_SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE),
        soundManager(),
        animation(gameContext, soundManager),
        camera(window),
        drawer(window, animation, gameContext, camera),
        eventHandler(dtoSender, gameContext, soundManager),
        matchDtoQueue(_events),
        lastUpdate(),
        isRunning_(true) {}

void UILoop::exec() {
    try {
        soundManager.playBackgroundMusic();

        while (isRunning_) {
            unsigned int frameStart = SDL_GetTicks();

            eventHandler.handle(isRunning_);

            update();

            drawer.draw(lastUpdate);

            frameDelay(frameStart);
        }
    } catch (const std::exception& e) {
        std::cerr << "Exception caught in UILoop" << e.what() << std::endl;
        isRunning_ = false;
    } catch (...) {
        std::cerr << "Unknown exception caught in UILoop" << std::endl;
        isRunning_ = false;
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

    camera.update(lastUpdate);

    animation.updateFrame();

    animation.updateSprite(lastUpdate);
}

void UILoop::frameDelay(unsigned int frameStart) {
    unsigned int frameTime = SDL_GetTicks() - frameStart;
    if (FRAME_DELAY > frameTime) {
        SDL_Delay(FRAME_DELAY - frameTime);
    }
}

UILoop::~UILoop() = default;
