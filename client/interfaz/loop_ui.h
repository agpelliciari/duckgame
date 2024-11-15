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

#define INITIAL_SCREEN_WIDTH 640
#define INITIAL_SCREEN_HEIGHT 480
#define FRAME_DELAY 16

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

    bool isRunning_;  // cppcheck-suppress unusedStructMember

    // This is where most of the game logic will go;
    // including: movement, AI, and animation updates.
    void update();

    void frameDelay(unsigned int frameStart);

public:
    UILoop(ActionListener& dtoSender, SimpleEventListener& _events, const GameContext& gameContext);

    void exec();

    ~UILoop();
};

#endif  // CLIENT_UI_LOOP_H_
