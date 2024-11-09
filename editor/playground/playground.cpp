#include "playground.h"
#include "ui_playground.h"

#include <QDir>
#include <QDebug>

#include <iostream>

Playground::Playground(const PlaygroundHandler& handler, QWidget* parent): QGraphicsView(parent), ui(new Ui::Playground), map(new QGraphicsScene(this)), handler(handler) {
    ui->setupUi(this);
    qRegisterMetaType<MapObjectData>("MapObjectData");

    initializeMap();
}

void Playground::setBackground(QPixmap pixelMap) {
    pixelMap = pixelMap.scaled(width * textureSize, height * textureSize, Qt::IgnoreAspectRatio);
    background->setBrush(pixelMap);
}

void Playground::addBlock(QPoint position, QPixmap pixelMap) {
    QGraphicsItem* graphicItem = map->itemAt(position, QTransform());

    if (!graphicItem || graphicItem->type() != QGraphicsRectItem::Type)
        return;

    QGraphicsRectItem* block = static_cast<QGraphicsRectItem*>(graphicItem);
    QBrush texture(pixelMap);
    block->setBrush(texture);

    MapObjectData mapObjectData = block->data(0).value<MapObjectData>();
    mapObjectData.mapObject = MapObject::Block;
    mapObjectData.texture = "";
    block->setData(0, QVariant::fromValue(mapObjectData));
}

void Playground::removeBlock(QPoint position) {
    QGraphicsItem* graphicItem = map->itemAt(position, QTransform());

    if (!graphicItem || graphicItem->type() != QGraphicsRectItem::Type)
        return;

    QGraphicsRectItem* block = static_cast<QGraphicsRectItem*>(graphicItem);
    block->setBrush(Qt::NoBrush);

    MapObjectData mapObjectData = block->data(0).value<MapObjectData>();
    mapObjectData.mapObject = MapObject::Empty;
    mapObjectData.texture = "";
    block->setData(0, QVariant::fromValue(mapObjectData));
}

std::vector<MapObjectData> Playground::blocks() {
    std::vector<MapObjectData> blocks;

    for (QGraphicsRectItem* mapObject : mapObjects) {
        MapObjectData mapObjectData = mapObject->data(0).value<MapObjectData>();
        if (mapObjectData.mapObject == MapObject::Block)
            blocks.push_back(mapObjectData);
    }

    return blocks;
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
    map->addItem(background);

    for (int row = 0; row < height; ++row) {
        for (int col = 0; col < width; ++col) {
            QGraphicsRectItem* mapObject = map->addRect(
                col * textureSize, row * textureSize, textureSize, textureSize,
                QPen(Qt::NoPen), Qt::NoBrush
            );
            mapObject->setZValue(2);
            mapObject->setData(0, QVariant::fromValue(MapObjectData{ row, col, MapObject::Empty, "" }));
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
    }
}

void Playground::zoom(int scaleFactor) {
    qreal qReal = scaleFactor / 100.0;
    resetTransform();
    scale(qReal, qReal);
}
