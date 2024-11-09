#ifndef PLAYGROUND_H
#define PLAYGROUND_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QBrush>
#include <QColor>
#include <QMouseEvent>

enum MapObject {
    Block,
    Decoration,
    Spawn,
    Box,
    Empty
};

struct MapObjectData {
    int row;
    int column;
    MapObject mapObject;
    std::string texture;
};

Q_DECLARE_METATYPE(MapObjectData)

struct PlaygroundHandler {
    std::function<void(QPoint)> onLeftClick;
    std::function<void(QPoint)> onRightClick;
};

namespace Ui {
class Playground;
}

class Playground : public QGraphicsView {
    Q_OBJECT

private:
    Ui::Playground* ui;
    QGraphicsScene* map;
    QGraphicsRectItem* background;
    std::vector<QGraphicsRectItem*> mapObjects;

    const PlaygroundHandler handler;

    const int width = 20;
    const int height = 10;
    const int textureSize = 16;

public:
    explicit Playground(const PlaygroundHandler& handler, QWidget* parent = nullptr);

    void setBackground(QPixmap pixelMap);

    void addBlock(QPoint position, QPixmap pixelMap);

    void removeBlock(QPoint position);

    std::vector<MapObjectData> blocks();

    ~Playground();

private:
    void initializeMap();

    void mousePressEvent(QMouseEvent* event) override;
};

#endif
