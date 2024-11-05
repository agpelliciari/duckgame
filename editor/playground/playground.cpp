#include "playground.h"
#include "ui_playground.h"

#include <QDir>
#include <QDebug>

Playground::Playground(QWidget* parent): QGraphicsView(parent), ui(new Ui::Playground), map(new QGraphicsScene(this)) {
    ui->setupUi(this);

    const int width = 20;
    const int height = 10;
    const int blockSize = 32;

    setScene(map);
    setupGrid(width, height, blockSize);
}

Playground::~Playground() {
    delete ui;
}

void Playground::setupGrid(int width, int height, int blockSize) {
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
    QPointF scenePos = mapToScene(event->pos());
    QGraphicsItem* block = map->itemAt(scenePos, QTransform());

    if (block && block->type() == QGraphicsRectItem::Type) {
        QGraphicsRectItem* blockRect = static_cast<QGraphicsRectItem*>(block);

        QPixmap texturePixmap;
        if (event->button() == Qt::LeftButton) {
            texturePixmap.load("./editor/bloque.png");
        } else if (event->button() == Qt::RightButton) {
            texturePixmap.load("./editor/pasto.png");
        }

        QBrush textureBrush(texturePixmap);
        blockRect->setBrush(textureBrush);
    }
}
