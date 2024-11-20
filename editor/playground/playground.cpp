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

    setMapObjectData(block, MapObjectType::Block, "") ;
    
    repainBlocksWith(tileSet);
}

void Playground::addSpawnPlayer(QPoint position, Texture texture) {
    QGraphicsRectItem* spawnPlayer = mapObjectAt(spawnPlayers, position);

    if (!spawnPlayer)
        return;

    QBrush brush(texture.pixelMap);
    spawnPlayer->setBrush(brush);
}

void Playground::addSpawnWeapon(QPoint position, Texture texture) {
    QGraphicsRectItem* spawnWeapon = mapObjectAt(spawnWeapons, position);

    if (!spawnWeapon)
        return;
    
    QBrush brush(texture.pixelMap);
    spawnWeapon->setBrush(brush);
}

void Playground::addBox(QPoint position, Texture texture) {
    QGraphicsRectItem* box = mapObjectAt(boxes, position);

    if (!box)
        return;
    
    QBrush brush(texture.pixelMap);
    box->setBrush(brush);
}

void Playground::addDecoration(QPoint position, Texture texture) {
    QGraphicsRectItem* decoration = mapObjectAt(decorations, position);

    if (!decoration)
        return;
    
    QBrush brush(texture.pixelMap);
    decoration->setBrush(brush);
}

void Playground::removeBlock(QPoint position, TileSet tileSet) {
    QGraphicsRectItem* block = mapObjectAt(blocks, position);

    if (!block)
        return;

    block->setBrush(Qt::NoBrush);
    cleanObjectData(block);

    repainBlocksWith(tileSet);
}

void Playground::removeSpawnPlayer(QPoint position) {
    QGraphicsRectItem* spawnPlayer = mapObjectAt(spawnPlayers, position);

    if (!spawnPlayer)
        return;

    spawnPlayer->setBrush(Qt::NoBrush);
    cleanObjectData(spawnPlayer);
}

void Playground::removeSpawnWeapon(QPoint position) {
    QGraphicsRectItem* spawnWeapon = mapObjectAt(spawnWeapons, position);

    if (!spawnWeapon)
        return;

    spawnWeapon->setBrush(Qt::NoBrush);
    cleanObjectData(spawnWeapon);
}

void Playground::removeBox(QPoint position) {
    QGraphicsRectItem* box = mapObjectAt(boxes, position);

    if (!box)
        return;

    box->setBrush(Qt::NoBrush);
    cleanObjectData(box);
}

void Playground::removeDecoration(QPoint position) {
    QGraphicsRectItem* decoration = mapObjectAt(decorations, position);

    if (!decoration)
        return;

    decoration->setBrush(Qt::NoBrush);
    cleanObjectData(decoration);
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
    return mapObjectsFilter(blocks, MapObjectType::Block);
}

std::vector<MapObjectData> Playground::spawnPlayersToExport() {
    return mapObjectsFilter(spawnPlayers, MapObjectType::SpawnPlayer);
}

std::vector<MapObjectData> Playground::spawnWeaponsToExport() {
    return mapObjectsFilter(spawnWeapons, MapObjectType::SpawnWeapon);
}

std::vector<MapObjectData> Playground::boxesToExport() {
    return mapObjectsFilter(boxes, MapObjectType::Box);
}

std::vector<MapObjectData> Playground::decorationsToExport() {
    return mapObjectsFilter(decorations, MapObjectType::Decoration);
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

void Playground::mousePressEvent(QMouseEvent* event) {
    QPointF position = mapToScene(event->pos());

    if (event->button() == Qt::LeftButton) {
        handler.onLeftClick(position.toPoint());
    } else if (event->button() == Qt::RightButton) {
        handler.onRightClick(position.toPoint());
    } else if (event->button() == Qt::MiddleButton) {
        isDragging = true;
        lastMousePosition = event->pos();
        setCursor(Qt::ClosedHandCursor);
        event->accept();
    } else {
        QGraphicsView::mousePressEvent(event);
    }
}

void Playground::mouseMoveEvent(QMouseEvent* event) {
    if (isDragging) {
        QPoint delta = event->pos() - lastMousePosition;
        lastMousePosition = event->pos();
        horizontalScrollBar()->setValue(horizontalScrollBar()->value() - delta.x());
        verticalScrollBar()->setValue(verticalScrollBar()->value() - delta.y());
        event->accept();
    } else {
        QGraphicsView::mouseMoveEvent(event);
    }
}

void Playground::mouseReleaseEvent(QMouseEvent* event) {
    if (event->button() == Qt::MiddleButton) {
        isDragging = false;
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

std::vector<MapObjectData> Playground::mapObjectsData(const std::vector<QGraphicsRectItem*>& rectItems) {
    std::vector<MapObjectData> result;

    for (QGraphicsRectItem* rectItem : rectItems) {
        MapObjectData mapObjectData = rectItem->data(0).value<MapObjectData>();
        MapObjectData newMapObjectData = {
            MAX_HEIGHT - mapObjectData.row - 1,
            mapObjectData.column,
            mapObjectData.zIndex,
            mapObjectData.mapObjectType,
            mapObjectData.texture,
        };
        result.push_back(newMapObjectData);
    }

    return result;
}
