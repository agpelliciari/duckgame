#include "camera.h"

Camera::Camera(SDL2pp::Window& window): window(window), x(0), y(0), zoom(1.0f) {}

void Camera::updateZoom(int boxWidth, int boxHeight) {
    float zoomX = static_cast<float>(window.GetWidth()) / (boxWidth + PADDING);
    float zoomY = static_cast<float>(window.GetHeight()) / (boxHeight + PADDING);

    // this is necessary to fit the entire group of players in the screen
    zoom = std::min(zoomX, zoomY);

    // range values for zoom in/out
    zoom = std::clamp(zoom, MIN_ZOOM_LEVEL, MAX_ZOOM_LEVEL);
}

void Camera::updatePosition(int minX, int minY, int boxWidth, int boxHeight) {
    x = minX + boxWidth / 2 - (window.GetWidth() / 2) / zoom;
    y = minY + boxHeight / 2 - (window.GetHeight() / 2) / zoom;
}

void Camera::update(const MatchDto& matchDto) {
    int firstPlayerX = matchDto.players[0].pos.x;
    int firstPlayerY = matchDto.players[0].pos.y;

    int minX = firstPlayerX;
    int maxX = firstPlayerX;
    int minY = firstPlayerY;
    int maxY = firstPlayerY;

    for (const PlayerDTO& player: matchDto.players) {
        if (player.pos.x < minX)
            minX = player.pos.x;
        if (player.pos.x > maxX)
            maxX = player.pos.x;
        if (player.pos.y < minY)
            minY = player.pos.y;
        if (player.pos.y > maxY)
            maxY = player.pos.y;
    }

    // bounding box dimensions
    int boxWidth = maxX - minX;
    int boxHeight = maxY - minY;

    updateZoom(boxWidth, boxHeight);

    updatePosition(minX, minY, boxWidth, boxHeight);
}

int Camera::getScreenX(int playerX) { return static_cast<int>((playerX - x) * zoom); }

int Camera::getScreenY(int playerY) { return static_cast<int>((playerY - y) * zoom); }

int Camera::getScaledSize(int size) { return static_cast<int>(size * zoom); }

SDL_Rect Camera::backgroundVisibleSection(int targetWidth, int targetHeight, float offSetFactor) const {
    int visibleWidth = static_cast<int>(targetWidth / zoom);
    int visibleHeight = static_cast<int>(targetHeight / zoom);

    int offsetX = static_cast<int>(x * offSetFactor) - visibleWidth / 2;
    int offsetY = static_cast<int>(y * offSetFactor) - visibleHeight / 2;

    offsetX = std::clamp(offsetX, 0, targetWidth - visibleWidth);
    offsetY = std::clamp(offsetY, 0, targetHeight - visibleHeight);

    return { offsetX, offsetY, visibleWidth, visibleHeight };
}

Camera::~Camera() = default;
