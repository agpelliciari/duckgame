#ifndef CAMERA_H
#define CAMERA_H

#include <algorithm>

#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>

#include "common/dtosgame.h"

#define PADDING 100

#define MIN_ZOOM_LEVEL 0.5f
#define MAX_ZOOM_LEVEL 2.0f

class Camera {
private:
    SDL2pp::Window& window;

    int x;  // cppcheck-suppress unusedStructMember

    int y;  // cppcheck-suppress unusedStructMember

    float zoom;  // cppcheck-suppress unusedStructMember

    void updateZoom(int boxWidth, int boxHeight);

    void updatePosition(int minX, int minY, int boxWidth, int boxHeight);

public:
    Camera(SDL2pp::Window& window);

    // Update the camera position and zoom level based on a bounding box which
    // contains all players in the match determined by their positions.
    void update(const MatchDto& matchDto);

    int getScreenX(int playerX);

    int getScreenY(int playerY);

    int getScaledSize(int size);

    int backgroundScaledSize(int size);

    ~Camera();
};

#endif
