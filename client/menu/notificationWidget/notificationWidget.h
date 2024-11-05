#ifndef NOTIFICATIONWIDGET_H
#define NOTIFICATIONWIDGET_H

#include <QFrame>
#include <QHBoxLayout>
#include <QLabel>
#include <QTimer>
#include <QWidget>

struct NotificationHandler {
    std::string label;
    std::function<void()> onClose;
};

namespace Ui {
class NotificationWidget;
}

class NotificationWidget: public QWidget {
    Q_OBJECT
private:
    const NotificationHandler handler;

public:
    explicit NotificationWidget(NotificationHandler handler, QWidget* parent = nullptr);

    ~NotificationWidget();

private:
    void onClose();
};

#endif
