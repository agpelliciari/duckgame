#ifndef PLAYGROUND_H
#define PLAYGROUND_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QBrush>
#include <QColor>
#include <QMouseEvent>

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
    Ui::Playground* ui;
    QGraphicsScene* map;
    QGraphicsRectItem* background;

    const PlaygroundHandler handler;

public:
    explicit Playground(const PlaygroundHandler& handler, QWidget* parent = nullptr);

    void setBackground(QPixmap texture);

    void addBlock(QPoint position, QBrush texture);

    void removeBlock(QPoint position);

    ~Playground();

private:
    void initializeMap(int width, int height, int blockSize);

    void mousePressEvent(QMouseEvent* event) override;
};

#endif
