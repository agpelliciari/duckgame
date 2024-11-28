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

        Clock clock(MS_PER_FRAME);

        clock.resetnext();

        while (isRunning_) {
            eventHandler.handle(isRunning_);

            update();

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

void UILoop::updateMatchStats() {
    MatchStatsInfo stats;
    while (isRunning_ && matchDtoQueue.update_stats(stats)) {
        lastStatsUpdate = stats;
    }
}

void UILoop::updateMatchDto() {
    MatchDto matchUpdate;
    while (isRunning_ && matchDtoQueue.try_update(matchUpdate)) {
        lastUpdate = matchUpdate;
    }
}

bool UILoop::updateMatchState() {
    if ((lastStatsUpdate.state == TERMINADA) || (lastStatsUpdate.state == CANCELADA)) {
        drawer.drawLeaderboard(lastStatsUpdate);
        return UPDATED;

    } else if (lastStatsUpdate.state == PAUSADA) {
        drawer.drawLeaderboard(lastStatsUpdate);
        return UPDATED;

    } else if (lastStatsUpdate.state == ROUND_END) {
        if (soundManager.isRoundEndSoundAvailable()) {
            soundManager.playSound(SoundType::ROUND_END);
            soundManager.setRoundEndSoundAvailability(false);
        }
        drawer.drawWinner(lastStatsUpdate, lastUpdate);
        return UPDATED;

    } else if(lastStatsUpdate.state == STARTED_ROUND){       
        drawer.resetIndicatorFlag();
        soundManager.setRoundEndSoundAvailability(true);
        lastStatsUpdate.state = INICIADA;
        return UPDATED;
    }

    return NOT_UPDATED;
}

void UILoop::update() {

    updateMatchStats();
    
    if (updateMatchState()) {
        return;
    }

    updateMatchDto();

    animation.update(lastUpdate);

    camera.update(lastUpdate);

    drawer.draw(lastUpdate, lastStatsUpdate);
}

UILoop::~UILoop() = default;
