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
        lastStatsUpdate = stats;
    }
    
    if (lastStatsUpdate.state == TERMINADA ||
        lastStatsUpdate.state == CANCELADA) {  // stats.state == PAUSADA? mostrar info, o round end.
        //isRunning_ = false;
        drawer.drawLeaderboard(lastStatsUpdate);
        return;
    } else if (lastStatsUpdate.state == PAUSADA) {
        drawer.drawLeaderboard(lastStatsUpdate);
        return;
    } else if (lastStatsUpdate.state == ROUND_END) {
        drawer.drawWinner(lastStatsUpdate, lastUpdate);
        return;
    } else if(lastStatsUpdate.state == STARTED_ROUND){
        #ifdef LOG_DBG // Serviria para filtrar logs.
        std::cout << "RESETED AT INIT ROUND\n";
        #endif
        std::cout << "ronda: " << lastStatsUpdate.numronda << std::endl;  // numero de ronda no se actualiza
        
        drawer.resetIndicatorFlag();
        
        //  Asi ya recibe matchdtos..
        lastStatsUpdate.state = INICIADA; 
        return;
    } 


    MatchDto matchUpdate;

    while (isRunning_ && matchDtoQueue.try_update(matchUpdate)) {
        lastUpdate = matchUpdate;
    }

    animation.updateFrame();

    animation.updateSprite(lastUpdate);

    camera.update(lastUpdate);
    drawer.draw(lastUpdate);
}

UILoop::~UILoop() = default;
