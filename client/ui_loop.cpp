#include "ui_loop.h"

UILoop::UILoop(): 
    sdlLib(SDL_INIT_VIDEO), 
    window("UILOOP demo", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_RESIZABLE),
    renderer(window, -1, SDL_RENDERER_ACCELERATED),
    sprites(renderer, DATA_PATH "/grey_duck.png"),
    vcenter(renderer.GetOutputHeight() / 2),
    is_running_(true),
    animation() {}

void UILoop::handleEvent() {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            is_running_ = false;
        } else if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
                case SDLK_RIGHT:
                    animation.setState(STATE_RUNNING_RIGHT);
                    animation.flip(false);
                    break;
                case SDLK_LEFT:
                    animation.setState(STATE_RUNNING_LEFT);
                    animation.flip(true);
                    break;
                case SDLK_ESCAPE: case SDLK_q:
                    is_running_ = false;
                    break;
            }
        } else if (event.type == SDL_KEYUP) {
            animation.setState(STATE_STANDING);
        }
    }
}

void UILoop::update() {
    animation.updateFrame();

    animation.updatePosition();

	if (animation.getPosition() > renderer.GetOutputWidth()) animation.setPosition(-50);

	if (animation.getPosition() < -50) animation.setPosition(renderer.GetOutputWidth());

    animation.updateSprite();
}

void UILoop::draw() {
    // Clear screen
	renderer.Clear();

    // Determine the flip mode based on the last direction
    SDL_RendererFlip flip = animation.isFacingLeft() ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;

    // Draw player sprite
	renderer.Copy(
			sprites,
			Rect(animation.getSpriteX(), animation.getSpriteY(), 32, 32),
			Rect((int)animation.getPosition(), vcenter - 50, 50, 50),
			0.0,
			Point(0, 0),
			flip
		);

	// Show rendered frame
	renderer.Present();

	// Frame limiter: sleep for a little bit to not eat 100% of CPU
	SDL_Delay(1);
}

bool UILoop::isRunning() const { return is_running_; }

UILoop::~UILoop() = default;
