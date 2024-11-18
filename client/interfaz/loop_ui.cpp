#include "loop_ui.h"

#include "common/clock.h"

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
        Clock clock(16);  // 16ms == 60fps
        clock.resetnext();
        while (isRunning_) {
            eventHandler.handle(isRunning_);

            update();

            if (isRunning_) {
                drawer.draw(lastUpdate);
            }

            clock.tickNoRest();
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

    MatchStatsInfo stats;
    while (isRunning_ && matchDtoQueue.update_stats(stats)) {
        auto start = std::chrono::steady_clock::now();
        if (stats.state == TERMINADA ||
            stats.state == CANCELADA) {  // stats.state == PAUSADA? mostrar info, o round end.
            isRunning_ = false;

            // test leaderboard
            while (std::chrono::steady_clock::now() - start < std::chrono::seconds(6)) {
                drawer.drawLeaderboard(stats);
            }

        } else if (stats.state == PAUSADA) {
            while (std::chrono::steady_clock::now() - start < std::chrono::seconds(6)) {
                drawer.drawLeaderboard(stats);
            }

        } else if (stats.state == ROUND_END) {
            while (std::chrono::steady_clock::now() - start < std::chrono::seconds(3)) {
                drawer.drawWinner(stats, lastUpdate);
            }
            drawer.resetIndicatorFlag();
        }
    }

    std::cout << "ronda: " << stats.numronda << std::endl;  // numero de ronda no se actualiza

    MatchDto matchUpdate;

    while (isRunning_ && matchDtoQueue.try_update(matchUpdate)) {
        lastUpdate = matchUpdate;
    }

    camera.update(lastUpdate);

    animation.updateFrame();

    animation.updateSprite(lastUpdate);
}

UILoop::~UILoop() = default;
