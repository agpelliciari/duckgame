#include "playground.h"
#include "ui_playground.h"

#include <QDir>
#include <QDebug>

#include <iostream>

Playground::Playground(const PlaygroundHandler& handler, QWidget* parent): QGraphicsView(parent), ui(new Ui::Playground), map(new QGraphicsScene(this)), handler(handler) {
    ui->setupUi(this);

    const int width = 20;
    const int height = 10;
    const int blockSize = 32;

    initializeMap(width, height, blockSize);
}

void Playground::setBackground(QPixmap texture) {
    const int width = 20;
    const int height = 10;
    const int blockSize = 32;
    texture = texture.scaled(width * blockSize, height * blockSize, Qt::IgnoreAspectRatio);
    background->setBrush(texture);
}

void Playground::addBlock(QPoint position, QBrush texture) {
    QGraphicsItem* graphicItem = map->itemAt(position, QTransform());

    if (!graphicItem || graphicItem->type() != QGraphicsRectItem::Type)
        return;

    QGraphicsRectItem* block = static_cast<QGraphicsRectItem*>(graphicItem);
    block->setBrush(texture);
}

void Playground::removeBlock(QPoint position) {
    QGraphicsItem* graphicItem = map->itemAt(position, QTransform());

    if (!graphicItem || graphicItem->type() != QGraphicsRectItem::Type)
        return;

    QGraphicsRectItem* block = static_cast<QGraphicsRectItem*>(graphicItem);
    block->setBrush(Qt::NoBrush);
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
            QGraphicsRectItem* blockRect = map->addRect(
                col * blockSize, row * blockSize, blockSize, blockSize,
                QPen(Qt::NoPen), Qt::NoBrush
            );
            blockRect->setZValue(2);
            blockRect->setData(0, row * width + col);
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
