#ifndef LOBBYGUESTWIDGET_H
#define LOBBYGUESTWIDGET_H

#include "../playerWidget/playerWidget.h"

#include <QWidget>

struct LobbyGuestHandler {
    std::function<void()> onClickCancel;
};

namespace Ui {
class LobbyGuestWidget;
}

class LobbyGuestWidget : public QWidget {
    Q_OBJECT

private:
    Ui::LobbyGuestWidget *ui;
    const LobbyGuestHandler handler;

public:
    explicit LobbyGuestWidget(const LobbyGuestHandler& handler, QWidget *parent = nullptr);

    void updateIdDisplayedInLobby(int id);

    void addPlayerToLobby(int n);

    ~LobbyGuestWidget();

private:
    void onClickCancel();
};

#endif
