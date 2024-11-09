#include "playground.h"
#include "ui_playground.h"

#include <QDir>
#include <QDebug>

#include <iostream>

Playground::Playground(const PlaygroundHandler& handler, QWidget* parent): QGraphicsView(parent), ui(new Ui::Playground), map(new QGraphicsScene(this)), handler(handler) {
    ui->setupUi(this);
    qRegisterMetaType<MapObjectData>("MapObjectData");

    const int width = 20;
    const int height = 10;
    const int blockSize = 16;

    initializeMap(width, height, blockSize);
}

void Playground::setBackground(QPixmap texture) {
    const int width = 20;
    const int height = 10;
    const int blockSize = 16;
    texture = texture.scaled(width * blockSize, height * blockSize, Qt::IgnoreAspectRatio);
    background->setBrush(texture);
}

void Playground::addBlock(QPoint position, QBrush texture) {
    QGraphicsItem* graphicItem = map->itemAt(position, QTransform());

    if (!graphicItem || graphicItem->type() != QGraphicsRectItem::Type)
        return;

    QGraphicsRectItem* block = static_cast<QGraphicsRectItem*>(graphicItem);
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

Playground::~Playground() {
    delete ui;
}

void Playground::initializeMap(int width, int height, int blockSize) {
    setScene(map);
    map->setSceneRect(0, 0, width * blockSize, height * blockSize);

    background = new QGraphicsRectItem(0, 0, width * blockSize, height * blockSize);
    background->setBrush(Qt::NoBrush);
    background->setPen(Qt::NoPen);
    background->setZValue(1);
    map->addItem(background);

    for (int row = 0; row < height; ++row) {
        for (int col = 0; col < width; ++col) {
            QGraphicsRectItem* mapObject = map->addRect(
                col * blockSize, row * blockSize, blockSize, blockSize,
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
