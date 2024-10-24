#ifndef UI_LOOP_H
#define UI_LOOP_H

#include <SDL2pp/SDL2pp.hh>
#include <SDL2/SDL.h>

#include "animation.h"

#define SCREEN_HEIGHT 480
#define SPRITE_WIDTH 32
#define SPRITE_HEIGHT 32
#define FRAME_DELAY 33
#define GROUND_Y 400  

using namespace SDL2pp;

class UILoop {
private:
    SDL sdlLib;

    Window window;

    Renderer renderer;

    Texture sprites;

    bool is_running_;

    Animation animation;
    
public:
    UILoop();

    bool isRunning() const;
    // Event processing: //TODO: Maquina de estados finita
		// - If window is closed, or Q or Escape buttons are pressed, quit the application
		// - If Right key is pressed, character would run
		// - If Right key is released, character would stop
        // TODO: - If Space key is pressed, character would jump
        // TODO: - If Down key is pressed, character would lay dead
    void handleEvent();

    // This is where most of the game logic will go; 
    //including: movement, AI, and animation updates.
    void update();

    //Any logic that relies on data calculated in the Update method will go here, 
    //for example: you could place collision logic here
    //TODO: void lateUpdate();

    //Once all the entities have been updated, we draw them to the screen. 
    //This method will be responsible for drawing everything, including the games UI.
    void draw();

    void frameDelay(unsigned int frameStart);
    
    ~UILoop();
};

#endif
