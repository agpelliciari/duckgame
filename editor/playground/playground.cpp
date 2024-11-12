#include "playground.h"
#include "ui_playground.h"

Playground::Playground(const PlaygroundHandler& handler, QWidget* parent): QGraphicsView(parent), ui(new Ui::Playground), map(new QGraphicsScene(this)), handler(handler) {
    ui->setupUi(this);
    qRegisterMetaType<MapObjectData>("MapObjectData");


    initializeMap();
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
    
    repainAllBlocksWith(tileSet);
}

void Playground::addPhysicalObject(QPoint position, Texture texture) {
    QGraphicsRectItem* physicalObject = mapObjectAt(physicalObjects, position);

    if (!physicalObject)
        return;

    QBrush brush(texture.pixelMap);
    physicalObject->setBrush(brush);

    setMapObjectData(physicalObject, texture.mapObjectType, texture.source);
}

void Playground::addNonPhysicalObject(QPoint position, Texture texture) {
    QGraphicsRectItem* nonPhysicalObject = mapObjectAt(nonPhysicalObjects, position);

    if (!nonPhysicalObject)
        return;

    QBrush brush(texture.pixelMap);
    nonPhysicalObject->setBrush(brush);

    setMapObjectData(nonPhysicalObject, texture.mapObjectType, texture.source);
}

void Playground::removeBlock(QPoint position, TileSet tileSet) {
    QGraphicsRectItem* block = mapObjectAt(blocks, position);

    if (!block)
        return;

    block->setBrush(Qt::NoBrush);
    cleanObjectData(block);

    repainAllBlocksWith(tileSet);
}

void Playground::removePhysicalObject(QPoint position) {
    QGraphicsRectItem* physicalObject = mapObjectAt(physicalObjects, position);

    if (!physicalObject)
        return;

    physicalObject->setBrush(Qt::NoBrush);
    cleanObjectData(physicalObject);
}

void Playground::removeNonPhysicalObject(QPoint position) {
    QGraphicsRectItem* nonPhysicalObject = mapObjectAt(nonPhysicalObjects, position);

    if (!nonPhysicalObject)
        return;

    nonPhysicalObject->setBrush(Qt::NoBrush);
    cleanObjectData(nonPhysicalObject);
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
    return mapObjectsFilter(nonPhysicalObjects, MapObjectType::SpawnPlayer);
}

std::vector<MapObjectData> Playground::spawnWeaponsToExport() {
    return mapObjectsFilter(nonPhysicalObjects, MapObjectType::SpawnWeapon);
}

std::vector<MapObjectData> Playground::boxesToExport() {
    return mapObjectsFilter(physicalObjects, MapObjectType::Box);
}

std::vector<MapObjectData> Playground::decorationsToExport() {
    return mapObjectsFilter(nonPhysicalObjects, MapObjectType::Decoration);
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

    createMapLayerFor(blocks, 1);
    createMapLayerFor(physicalObjects, 2);
    createMapLayerFor(nonPhysicalObjects, 3);
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

void Playground::repainAllBlocksWith(TileSet tileSet) {
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

std::vector<MapObjectData> Playground::mapObjectsFilter(const std::vector<QGraphicsRectItem*>& mapObjects, MapObjectType mapObjectType) {
    std::vector<MapObjectData> result;

    for (QGraphicsRectItem* mapObject : mapObjects) {
        MapObjectData mapObjectData = mapObject->data(0).value<MapObjectData>();
        if (mapObjectData.mapObjectType == mapObjectType)
            result.push_back(mapObjectData);
    }

    return result;
}
