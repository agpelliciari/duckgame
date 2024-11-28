#ifndef CLIENT_UI_LOOP_H_
#define CLIENT_UI_LOOP_H_

#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>

#include "client/actionlistener.h"
#include "client/gamecontext.h"
#include "client/interfaz/event_handler.h"
#include "client/simpleeventlistener.h"
#include "common/dtosgame.h"

#include "animation.h"
#include "camera.h"
#include "drawer.h"
#include "sound_manager.h"

#define MS_PER_FRAME 16  // 16ms == 60fps
#define UPDATED true
#define NOT_UPDATED false

class UILoop {
private:
    SDL2pp::SDL sdlLib;

    SDL2pp::Window window;

    SoundManager soundManager;

    Animation animation;

    Camera camera;

    Drawer drawer;

    EventHandler eventHandler;

    SimpleEventListener& matchDtoQueue;

    MatchDto lastUpdate;

    MatchStatsInfo lastStatsUpdate;

    bool isRunning_;  // cppcheck-suppress unusedStructMember

    void updateMatchStats();

    void updateMatchDto();

    bool updateMatchState();

    // This is where most of the game logic will go;
    // including: movement, AI, and animation updates.
    void update();

public:
    UILoop(ActionListener& dtoSender, SimpleEventListener& _events, const GameContext& gameContext);

    void exec();

    ~UILoop();
};

#endif  // CLIENT_UI_LOOP_H_
