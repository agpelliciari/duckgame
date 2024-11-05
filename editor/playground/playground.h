#ifndef PLAYGROUND_H
#define PLAYGROUND_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QBrush>
#include <QColor>
#include <QMouseEvent>

namespace Ui {
class Playground;
}

class Playground : public QGraphicsView {
    Q_OBJECT

private:
    Ui::Playground* ui;
    QGraphicsScene* map;

public:
    explicit Playground(QWidget* parent = nullptr);

    ~Playground();

private:
    void setupGrid(int width, int height, int blockSize);

    void mousePressEvent(QMouseEvent* event) override;
};

#endif
