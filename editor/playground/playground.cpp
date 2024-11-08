#include "playground.h"
#include "ui_playground.h"

#include <QDir>
#include <QDebug>

Playground::Playground(const PlaygroundHandler& handler, QWidget* parent): QGraphicsView(parent), ui(new Ui::Playground), map(new QGraphicsScene(this)), handler(handler) {
    ui->setupUi(this);

    const int width = 20;
    const int height = 10;
    const int blockSize = 32;

    initializeMap(width, height, blockSize);
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

    QBrush blueBrush(QColor(0, 0, 255));
    QBrush redBrush(QColor(255, 0, 0));

    for (int row = 0; row < height; ++row) {
        for (int col = 0; col < width; ++col) {
            QBrush& currentBrush = (row + col) % 2 == 0 ? blueBrush : redBrush;
            QGraphicsRectItem* blockRect = map->addRect(
                col * blockSize, row * blockSize, blockSize, blockSize,
                QPen(Qt::NoPen), currentBrush
            );

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
