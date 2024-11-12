#ifndef PLAYGROUND_H
#define PLAYGROUND_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QBrush>
#include <QColor>
#include <QMouseEvent>

#include "../types.h"

struct MapObjectData {
    int row;
    int column;
    MapObjectType mapObjectType;
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
    static constexpr int ZOOM_STEP = 50;
    static constexpr int ZOOM_MIN = 100;
    static constexpr int ZOOM_MAX = 300;

    Ui::Playground* ui;
    QGraphicsScene* map;
    const PlaygroundHandler handler;

    QGraphicsRectItem* background;
    std::vector<QGraphicsRectItem*> physicalObjects;
    std::vector<QGraphicsRectItem*> nonPhysicalObjects;

    int scaleFactor = ZOOM_MIN;
    const int width = 20;
    const int height = 10;
    const int textureSize = 16;

public:
    explicit Playground(const PlaygroundHandler& handler, QWidget* parent = nullptr);

    void setBackground(Texture texture);

    void addPhysicalObject(QPoint position, Texture texture);

    void addNonPhysicalObject(QPoint position, Texture texture);

    void removePhysicalObject(QPoint position);

    void removeNonPhysicalObject(QPoint position);

    MapObjectData backgroundToExport();

    std::vector<MapObjectData> blocksToExport();

    std::vector<MapObjectData> spawnPlayersToExport();

    std::vector<MapObjectData> spawnWeaponsToExport();

    std::vector<MapObjectData> boxesToExport();

    std::vector<MapObjectData> decorationsToExport();

    void zoomIn();

    void zoomOut();

    ~Playground();

private:
    void initializeMap();

    void mousePressEvent(QMouseEvent* event) override;

    void zoom(int scaleFactor);

    void setMapObjectData(QGraphicsRectItem* mapObject, MapObjectType mapObjectType, const std::string& texture);

    void cleanObjectData(QGraphicsRectItem* mapObject);

    QGraphicsRectItem* mapObjectAt(std::vector<QGraphicsRectItem*> mapObjects, QPoint position);

    std::vector<MapObjectData> mapObjectsFilter(const std::vector<QGraphicsRectItem*>& mapObjects, MapObjectType mapObjectType);
};

#endif
