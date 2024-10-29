#ifndef LOBBYHOSTWIDGET_H
#define LOBBYHOSTWIDGET_H

#include <QWidget>

struct LobbyHostHandler {
    std::function<void()> onClickStart;
    std::function<void()> onClickCancel;
};

namespace Ui {
class LobbyHostWidget;
}

class LobbyHostWidget : public QWidget {
    Q_OBJECT

private:
    Ui::LobbyHostWidget *ui;
    const LobbyHostHandler handler;

public:
    explicit LobbyHostWidget(const LobbyHostHandler& handler, QWidget *parent = nullptr);

    ~LobbyHostWidget();

private:
    void onClickStart();

    void onClickCancel();
};

#endif
