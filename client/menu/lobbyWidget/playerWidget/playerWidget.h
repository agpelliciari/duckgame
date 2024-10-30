#ifndef PLAYERWIDGET_H
#define PLAYERWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QFrame>
#include <QLabel>
#include <QPushButton>

namespace Ui {
class PlayerWidget;
}

class PlayerWidget : public QWidget {
    Q_OBJECT
private:
    int n;

public:
    explicit PlayerWidget(int n, QWidget *parent = nullptr);

    ~PlayerWidget();

private:
    QString backgroundColorFor(int n);

    QString borderColorFor(int n);

};

#endif
