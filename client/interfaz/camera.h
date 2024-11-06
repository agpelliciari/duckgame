#ifndef CAMERA_H
#define CAMERA_H

#include <algorithm>

#include "common/dtos.h"
#include "common/dtosplayer.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define PADDING 100

class Camera {
private:
    int x;  // cppcheck-suppress unusedStructMember

    int y;  // cppcheck-suppress unusedStructMember

    float zoom;  // cppcheck-suppress unusedStructMember

    void updateZoom(int boxWidth, int boxHeight);

    void updatePosition(int minX, int minY, int boxWidth, int boxHeight);

public:
    Camera();

    // Update the camera position and zoom level based on a bounding box which
    // contains all players in the match determined by their positions.
    void update(const MatchDto& matchDto);

    int getScreenX(int playerX);

    int getScreenY(int playerY);

    int getScaledSize(int size);

    ~Camera();
};

#endif
