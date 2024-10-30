#ifndef PLAYERWIDGET_H
#define PLAYERWIDGET_H

#include <QFrame>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QWidget>

namespace Ui {
class PlayerWidget;
}

class PlayerWidget: public QWidget {
    Q_OBJECT
private:
    int n;  // cppcheck-suppress unusedStructMember

public:
    explicit PlayerWidget(int n, QWidget* parent = nullptr);

    ~PlayerWidget();

private:
    QString backgroundColorFor(int n);

    QString borderColorFor(int n);
};

#endif
