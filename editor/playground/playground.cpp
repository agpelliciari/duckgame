#include "playground.h"
#include "ui_playground.h"

Playground::Playground(const PlaygroundHandler& handler, QWidget* parent): QGraphicsView(parent), ui(new Ui::Playground), map(new QGraphicsScene(this)), handler(handler) {
    ui->setupUi(this);
    qRegisterMetaType<MapObjectData>("MapObjectData");

    initializeMap();
}

void Playground::zoomIn() {
    if (scaleFactor < ZOOM_MAX)
        scaleFactor += ZOOM_STEP;
    zoom(scaleFactor);
}

void Playground::zoomOut() {
    if (scaleFactor > ZOOM_MIN)
        scaleFactor -= ZOOM_STEP;
    zoom(scaleFactor);
}

void Playground::setBackground(Texture texture) {
    QPixmap pixelMap = texture.pixelMap.scaled(MAX_WIDTH * TEXTURE_SIZE, MAX_HEIGHT * TEXTURE_SIZE, Qt::IgnoreAspectRatio);
    background->setBrush(pixelMap);

    setMapObjectData(background, texture.mapObjectType, texture.source) ;
}

void Playground::addBlock(QPoint position, TileSet tileSet) {
    QGraphicsRectItem* block = mapObjectAt(blocks, position);

    if (!block)
        return;

    setMapObjectData(block, MapObjectType::Block, "");
    
    repainBlocksWith(tileSet);
}

void Playground::addSpawnPlayer(QPoint position, Texture texture) {
    addMapObject(position, spawnPlayers, MapObjectType::SpawnPlayer, texture);
}

void Playground::addSpawnWeapon(QPoint position, Texture texture) {
    addMapObject(position, spawnWeapons, MapObjectType::SpawnWeapon, texture);
}

void Playground::addBox(QPoint position, Texture texture) {
    addMapObject(position, boxes, MapObjectType::Box, texture);
}

void Playground::addDecoration(QPoint position, Texture texture) {
    addMapObject(position, decorations, MapObjectType::Decoration, texture);
}

void Playground::removeBlock(QPoint position, TileSet tileSet) {
    removeMapObject(position, blocks);
    repainBlocksWith(tileSet);
}

void Playground::removeSpawnPlayer(QPoint position) {
    removeMapObject(position, spawnPlayers);
}

void Playground::removeSpawnWeapon(QPoint position) {
    removeMapObject(position, spawnWeapons);
}

void Playground::removeBox(QPoint position) {
    removeMapObject(position, boxes);
}

void Playground::removeDecoration(QPoint position) {
    removeMapObject(position, decorations);
}

int Playground::maxWidthToExport() {
    return MAX_WIDTH;
}

int Playground::maxHeightToExport() {
    return MAX_HEIGHT;
}

MapObjectData Playground::backgroundToExport() {
    return background->data(0).value<MapObjectData>();
}

std::vector<MapObjectData> Playground::blocksToExport() {
    return mapObjectsDataToExport(mapObjectsFilter(blocks, MapObjectType::Block));
}

std::vector<MapObjectData> Playground::spawnPlayersToExport() {
    return mapObjectsDataToExport(mapObjectsFilter(spawnPlayers, MapObjectType::SpawnPlayer));
}

std::vector<MapObjectData> Playground::spawnWeaponsToExport() {
    return mapObjectsDataToExport(mapObjectsFilter(spawnWeapons, MapObjectType::SpawnWeapon));
}

std::vector<MapObjectData> Playground::boxesToExport() {
    return mapObjectsDataToExport(mapObjectsFilter(boxes, MapObjectType::Box));
}

std::vector<MapObjectData> Playground::decorationsToExport() {
    return mapObjectsDataToExport(mapObjectsFilter(decorations, MapObjectType::Decoration));
}

void Playground::cleanMap() {
    cleanMapObjects(blocks);
    cleanMapObjects(spawnPlayers);
    cleanMapObjects(spawnWeapons);
    cleanMapObjects(boxes);
    cleanMapObjects(decorations);
}

QPoint Playground::position(int column, int row) {
    int x = (column + 0.5) * TEXTURE_SIZE;
    int y = (MAX_HEIGHT - row - 0.5) * TEXTURE_SIZE;
    return QPoint(x, y);
}

Playground::~Playground() {
    delete ui;
}

void Playground::initializeMap() {
    setScene(map);
    map->setSceneRect(0, 0, MAX_WIDTH * TEXTURE_SIZE, MAX_HEIGHT * TEXTURE_SIZE);

    background = new QGraphicsRectItem(0, 0, MAX_WIDTH * TEXTURE_SIZE, MAX_HEIGHT * TEXTURE_SIZE);
    background->setBrush(Qt::NoBrush);
    background->setPen(Qt::NoPen);
    background->setZValue(1);
    background->setData(0, QVariant::fromValue(MapObjectData{ 1, 1, 1, MapObjectType::Empty, "" }));
    map->addItem(background);

    createMapLayerFor(decorations, 1);
    createMapLayerFor(blocks, 2);
    createMapLayerFor(boxes, 3);
    createMapLayerFor(spawnPlayers, 4);
    createMapLayerFor(spawnWeapons, 5);
}

void Playground::createMapLayerFor(std::vector<QGraphicsRectItem*>& mapObjects, int zIndex) {
    for (int row = 0; row < MAX_HEIGHT; ++row) {
        for (int col = 0; col < MAX_WIDTH; ++col) {
            QGraphicsRectItem* mapObject = map->addRect(
                col * TEXTURE_SIZE, row * TEXTURE_SIZE, TEXTURE_SIZE, TEXTURE_SIZE,
                QPen(Qt::NoPen), Qt::NoBrush
            );
            mapObject->setZValue(zIndex);
            mapObject->setData(0, QVariant::fromValue(MapObjectData{ row, col, zIndex, MapObjectType::Empty, "" }));
            mapObjects.push_back(mapObject);
        }
    }
}

void Playground::cleanMapObjects(const std::vector<QGraphicsRectItem*>& mapObjects) {
    for (QGraphicsRectItem* mapObject : mapObjects) {
        cleanObjectData(mapObject);
        mapObject->setBrush(Qt::NoBrush);
    }
}

void Playground::mousePressEvent(QMouseEvent* event) {
    QPointF position = mapToScene(event->pos());
    isDragging = true;
    lastMousePosition = event->pos();

    if (event->button() == Qt::LeftButton) {
        handler.onLeftClick(position.toPoint());
        event->accept();
    } else if (event->button() == Qt::RightButton) {
        handler.onRightClick(position.toPoint());
        event->accept();
    } else if (event->button() == Qt::MiddleButton) {
        setCursor(Qt::ClosedHandCursor);
        event->accept();
    } else {
        QGraphicsView::mousePressEvent(event);
    }
}

void Playground::mouseMoveEvent(QMouseEvent* event) {
    if (isDragging) {
        QPointF position = mapToScene(event->pos());
        if (event->buttons() & Qt::LeftButton) {
            handler.onLeftClick(position.toPoint());
        } else if (event->buttons() & Qt::RightButton) {
            handler.onRightClick(position.toPoint());
        } else {
            QPoint delta = event->pos() - lastMousePosition;
            horizontalScrollBar()->setValue(horizontalScrollBar()->value() - delta.x());
            verticalScrollBar()->setValue(verticalScrollBar()->value() - delta.y());
        }
        lastMousePosition = event->pos();
        event->accept();
    } else {
        QGraphicsView::mouseMoveEvent(event);
    }
}

void Playground::mouseReleaseEvent(QMouseEvent* event) {
    isDragging = false;
    if (event->button() == Qt::MiddleButton) {
        setCursor(Qt::ArrowCursor);
        event->accept();
    } else {
        QGraphicsView::mouseReleaseEvent(event);
    }
}

void Playground::zoom(int scaleFactor) {
    qreal qReal = scaleFactor / 100.0;
    resetTransform();
    scale(qReal, qReal);
}

void Playground::addMapObject(QPoint position, const std::vector<QGraphicsRectItem*>& mapObjects, MapObjectType mapObjectType, Texture texture) {
    QGraphicsRectItem* mapObject = mapObjectAt(mapObjects, position);

    if (!mapObject)
        return;
    
    setMapObjectData(mapObject, mapObjectType, texture.source);
    QBrush brush(texture.pixelMap);
    mapObject->setBrush(brush);
}

void Playground::removeMapObject(QPoint position, const std::vector<QGraphicsRectItem*>& mapObjects) {
    QGraphicsRectItem* mapObject = mapObjectAt(mapObjects, position);

    if (!mapObject)
        return;

    mapObject->setBrush(Qt::NoBrush);
    cleanObjectData(mapObject);
}

void Playground::setMapObjectData(QGraphicsRectItem* mapObject, MapObjectType mapObjectType, const std::string& texture) {
    MapObjectData mapObjectData = mapObject->data(0).value<MapObjectData>();
    mapObjectData.mapObjectType = mapObjectType;
    mapObjectData.texture = texture;
    mapObject->setData(0, QVariant::fromValue(mapObjectData));
}

void Playground::cleanObjectData(QGraphicsRectItem* mapObject) {
    setMapObjectData(mapObject, MapObjectType::Empty, "");
}

void Playground::repainBlocksWith(TileSet tileSet) {
    std::vector<MapObjectData> allMapObjectBlocks = mapObjectsFilter(blocks, MapObjectType::Block);

    for (QGraphicsRectItem* block : blocks) {
        MapObjectData blockObjectData = block->data(0).value<MapObjectData>();

        if (blockObjectData.mapObjectType == MapObjectType::Block) {
            Texture texture = tileSet.textureFor(stringRepresentationOfAdyacentsBlocks(blockObjectData, allMapObjectBlocks));

            QBrush brush(texture.pixelMap);
            block->setBrush(brush);

            setMapObjectData(block, texture.mapObjectType, texture.source);
        }
    }
}

std::string Playground::stringRepresentationOfAdyacentsBlocks(MapObjectData centerBlock, const std::vector<MapObjectData>& allMapObjectBlocks) {
    std::string result = "000000000";

    int index = 0;
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if (i == 0 && j == 0) {
                index++;
                continue;
            }
            
            int adjRow = centerBlock.row + i;
            int adjCol = centerBlock.column + j;
            
            for (const auto& block : allMapObjectBlocks) {
                if (block.row == adjRow && block.column == adjCol) {
                    result[index] = '1';
                    break;
                }
            }
            
            index++;
        }
    }
    
    return result;
}

std::vector<MapObjectData> Playground::mapObjectsFilter(const std::vector<QGraphicsRectItem*>& mapObjects, MapObjectType mapObjectType) {
    std::vector<MapObjectData> result;

    for (QGraphicsRectItem* mapObject : mapObjects) {
        MapObjectData mapObjectData = mapObject->data(0).value<MapObjectData>();
        if (mapObjectData.mapObjectType == mapObjectType)
            result.push_back(mapObjectData);
    }

    return result;
}

QGraphicsRectItem* Playground::mapObjectAt(std::vector<QGraphicsRectItem*> mapObjects, QPoint position) {
    int column = static_cast<int>(position.x()) / TEXTURE_SIZE;
    int row = static_cast<int>(position.y()) / TEXTURE_SIZE;

    if (column < 0 || column >= MAX_WIDTH || row < 0 || row >= MAX_HEIGHT)
        return nullptr;

    for (QGraphicsRectItem* mapObject : mapObjects) {
        MapObjectData mapObjectData = mapObject->data(0).value<MapObjectData>();

        if (mapObjectData.row == row && mapObjectData.column == column)
            return mapObject;
    }

    throw std::runtime_error("MapObject was not found inside the map");
}

std::vector<MapObjectData> Playground::mapObjectsDataToExport(const std::vector<MapObjectData>& mapObjects) {
    std::vector<MapObjectData> result;

    for (const MapObjectData& mapObjectData : mapObjects) {
        MapObjectData mapObjectDataToExport = {
            MAX_HEIGHT - mapObjectData.row - 1,
            mapObjectData.column,
            mapObjectData.zIndex,
            mapObjectData.mapObjectType,
            mapObjectData.texture,
        };
        result.push_back(mapObjectDataToExport);
    }

    return result;
}
