#include "playerWidget.h"

PlayerWidget::PlayerWidget(int n, QWidget *parent) : QWidget(parent), n(n) {
    QHBoxLayout* horizontalLayout = new QHBoxLayout(this);
    
    QFrame* color = new QFrame(this);
    color->setMinimumSize(QSize(20, 20));
    color->setMaximumSize(QSize(20, 20));
    color->setStyleSheet(QString("background-color: %1; border: 1px solid %2;").arg(backgroundColorFor(n)).arg(borderColorFor(n)));
    color->setFrameShape(QFrame::StyledPanel);
    color->setFrameShadow(QFrame::Raised);
    
    QLabel* name = new QLabel(QString("Player %1").arg(n), this);
    name->setAlignment(Qt::AlignCenter);

    horizontalLayout->addWidget(color);
    horizontalLayout->addWidget(name);
    
    setLayout(horizontalLayout);
}

PlayerWidget::~PlayerWidget() {
}

QString PlayerWidget::backgroundColorFor(int n) {
    switch (n) {
        case 1:
            return QString("#6db1ff");
        case 2:
            return QString("#fe7070");
        case 3:
            return QString("#54c45e");
        case 4:
            return QString("#ffe342");
        default:
            return QString("#ced4db");
    }
}

QString PlayerWidget::borderColorFor(int n) {
    switch (n) {
        case 1:
            return QString("#1071e5");
        case 2:
            return QString("#e81313");
        case 3:
            return QString("#008a0e");
        case 4:
            return QString("#fcce14");
        default:
            return QString("#979ea8");
    }
}