#include "notificationWidget.h"

NotificationWidget::NotificationWidget(NotificationHandler handler, QWidget* parent):
        QWidget(parent), handler(handler) {
    setStyleSheet("background-color: #b31616; color: white; padding: 10px 5px;");

    QHBoxLayout* horizontalLayout = new QHBoxLayout(this);

    QLabel* label = new QLabel(QString::fromStdString(handler.label), this);
    label->setAlignment(Qt::AlignCenter);

    horizontalLayout->addWidget(label, 1);

    setLayout(horizontalLayout);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    QTimer::singleShot(4000, this, &NotificationWidget::onClose);
}

void NotificationWidget::onClose() {
    if (handler.onClose)
        handler.onClose();
}

NotificationWidget::~NotificationWidget() {}
