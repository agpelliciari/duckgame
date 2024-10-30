#ifndef SETHOSTNAMEPORTWIDGET_H
#define SETHOSTNAMEPORTWIDGET_H

#include <QWidget>

struct SetHostnamePortHandler {
    std::function<void()> onClickContinue;
    std::function<void()> onClickQuit;
};

namespace Ui {
class SetHostnamePortWidget;
}

class SetHostnamePortWidget : public QWidget {
    Q_OBJECT

private:
    Ui::SetHostnamePortWidget *ui;
    const SetHostnamePortHandler handler;

public:
    explicit SetHostnamePortWidget(const SetHostnamePortHandler& handler, QWidget *parent = nullptr);

    ~SetHostnamePortWidget();

private:
    void onClickContinue();

    void onClickQuit();
};

#endif
