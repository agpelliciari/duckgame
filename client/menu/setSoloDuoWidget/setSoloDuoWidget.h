#ifndef SETSOLODUOWIDGET_H
#define SETSOLODUOWIDGET_H

#include <QWidget>

struct SetSoloDuoHandler {
    std::function<void()> onClickSolo;
    std::function<void()> onClickDuo;
    std::function<void()> onClickCancel;
};

namespace Ui {
class SetSoloDuoWidget;
}

class SetSoloDuoWidget : public QWidget {
    Q_OBJECT

private:
    Ui::SetSoloDuoWidget *ui;
    const SetSoloDuoHandler handler;

public:
    explicit SetSoloDuoWidget(const SetSoloDuoHandler& handler, QWidget *parent = nullptr);

    ~SetSoloDuoWidget();

private:
    void onClickSolo();

    void onClickDuo();

    void onClickCancel();
};

#endif
