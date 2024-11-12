#ifndef PLAYGROUND_H
#define PLAYGROUND_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QBrush>
#include <QColor>
#include <QMouseEvent>
#include <QScrollBar>


#include "../types.h"
#include "../tileset.h"

struct MapObjectData {
    int row;
    int column;
    int zIndex;
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
    static constexpr int MAX_WIDTH = 50;
    static constexpr int MAX_HEIGHT = 40;
    static constexpr int TEXTURE_SIZE = 16;

    static constexpr int ZOOM_STEP = 50;
    static constexpr int ZOOM_MIN = 100;
    static constexpr int ZOOM_MAX = 300;

    Ui::Playground* ui;
    QGraphicsScene* map;
    const PlaygroundHandler handler;

    QGraphicsRectItem* background;
    std::vector<QGraphicsRectItem*> blocks;
    std::vector<QGraphicsRectItem*> physicalObjects;
    std::vector<QGraphicsRectItem*> nonPhysicalObjects;

    int scaleFactor = ZOOM_MIN;
    bool isDragging = false;
    QPoint lastMousePosition;

public:
    explicit Playground(const PlaygroundHandler& handler, QWidget* parent = nullptr);

    void setBackground(Texture texture);

    void addBlock(QPoint position, TileSet tileSet);

    void addPhysicalObject(QPoint position, Texture texture);

    void addNonPhysicalObject(QPoint position, Texture texture);

    void removeBlock(QPoint position, TileSet tileSet);

    void removePhysicalObject(QPoint position);

    void removeNonPhysicalObject(QPoint position);

    int maxWidthToExport();

    int maxHeightToExport();

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

    void wheelEvent(QWheelEvent */*event*/) override {};

    void mousePressEvent(QMouseEvent* event) override;

    void mouseReleaseEvent(QMouseEvent* event) override;

    void mouseMoveEvent(QMouseEvent* event) override;

    void zoom(int scaleFactor);

    void setMapObjectData(QGraphicsRectItem* mapObject, MapObjectType mapObjectType, const std::string& texture);

    void cleanObjectData(QGraphicsRectItem* mapObject);

    void createMapLayerFor(std::vector<QGraphicsRectItem*>& mapObjects, int zIndex);

    void repainAllBlocksWith(TileSet tileSet);

    void repainBlocksWith(TileSet tileSet);

    std::string stringRepresentationOfAdyacentsBlocks(MapObjectData centerBlock, const std::vector<MapObjectData>& allMapObjectBlocks);

    QGraphicsRectItem* mapObjectAt(std::vector<QGraphicsRectItem*> mapObjects, QPoint position);

    std::vector<MapObjectData> mapObjectsFilter(const std::vector<QGraphicsRectItem*>& mapObjects, MapObjectType mapObjectType);
};

#endif
