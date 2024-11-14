#include "playground.h"
#include "ui_playground.h"

Playground::Playground(const PlaygroundHandler& handler, QWidget* parent): QGraphicsView(parent), ui(new Ui::Playground), map(new QGraphicsScene(this)), handler(handler) {
    ui->setupUi(this);
    qRegisterMetaType<MapObjectData>("MapObjectData");

    initializeMap();
}

void Playground::setBackground(Texture texture) {
    QPixmap pixelMap = texture.pixelMap.scaled(width * textureSize, height * textureSize, Qt::IgnoreAspectRatio);
    background->setBrush(pixelMap);

    setMapObjectData(background, texture.mapObjectType, texture.source) ;
}

void Playground::addPhysicalObject(QPoint position, Texture texture) {
    QGraphicsRectItem* physicalObject = mapObjectAt(physicalObjects, position);

    if (!physicalObject)
        return;

    QBrush brush(texture.pixelMap);
    physicalObject->setBrush(brush);

    setMapObjectData(physicalObject, texture.mapObjectType, texture.source) ;
}

void Playground::addNonPhysicalObject(QPoint position, Texture texture) {
    QGraphicsRectItem* nonPhysicalObject = mapObjectAt(nonPhysicalObjects, position);

    if (!nonPhysicalObject)
        return;

    QBrush brush(texture.pixelMap);
    nonPhysicalObject->setBrush(brush);

    setMapObjectData(nonPhysicalObject, texture.mapObjectType, texture.source) ;
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

MapObjectData Playground::backgroundToExport() {
    return background->data(0).value<MapObjectData>();
}

std::vector<MapObjectData> Playground::blocksToExport() {
    return mapObjectsFilter(physicalObjects, MapObjectType::Block);
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
    map->setSceneRect(0, 0, width * textureSize, height * textureSize);

    background = new QGraphicsRectItem(0, 0, width * textureSize, height * textureSize);
    background->setBrush(Qt::NoBrush);
    background->setPen(Qt::NoPen);
    background->setZValue(1);
    background->setData(0, QVariant::fromValue(MapObjectData{ 1, 1, 1, MapObjectType::Empty, "" }));
    map->addItem(background);

    for (int row = 0; row < height; ++row) {
        for (int col = 0; col < width; ++col) {
            QGraphicsRectItem* physicalObject = map->addRect(
                col * textureSize, row * textureSize, textureSize, textureSize,
                QPen(Qt::NoPen), Qt::NoBrush
            );
            physicalObject->setZValue(2);
            physicalObject->setData(0, QVariant::fromValue(MapObjectData{ row, col, 2, MapObjectType::Empty, "" }));
            physicalObjects.push_back(physicalObject);
        }
    }

    for (int row = 0; row < height; ++row) {
        for (int col = 0; col < width; ++col) {
            QGraphicsRectItem* nonPhysicalObject = map->addRect(
                col * textureSize, row * textureSize, textureSize, textureSize,
                QPen(Qt::NoPen), Qt::NoBrush
            );
            nonPhysicalObject->setZValue(3);
            nonPhysicalObject->setData(0, QVariant::fromValue(MapObjectData{ row, col, 3, MapObjectType::Empty, "" }));
            nonPhysicalObjects.push_back(nonPhysicalObject);
        }
    }
}

void Playground::mousePressEvent(QMouseEvent* event) {
    QPointF position = mapToScene(event->pos());

    if (event->button() == Qt::LeftButton) {
        handler.onLeftClick(position.toPoint());
    } else if (event->button() == Qt::RightButton) {
        handler.onRightClick(position.toPoint());
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

QGraphicsRectItem* Playground::mapObjectAt(std::vector<QGraphicsRectItem*> mapObjects, QPoint position) {
    int column = static_cast<int>(position.x()) / textureSize;
    int row = static_cast<int>(position.y()) / textureSize;

    if (column < 0 || column >= width || row < 0 || row >= height)
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