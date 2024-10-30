#ifndef LOBBYHOSTWIDGET_H
#define LOBBYHOSTWIDGET_H

#include <QWidget>

#include "../playerWidget/playerWidget.h"

struct LobbyHostHandler {
    std::function<void()> onClickStart;
    std::function<void()> onClickCancel;
};

namespace Ui {
class LobbyHostWidget;
}

class LobbyHostWidget: public QWidget {
    Q_OBJECT

private:
    Ui::LobbyHostWidget* ui;         // cppcheck-suppress unusedStructMember
    const LobbyHostHandler handler;  // cppcheck-suppress unusedStructMember

public:
    explicit LobbyHostWidget(const LobbyHostHandler& handler, QWidget* parent = nullptr);

    void updateIdDisplayedInLobby(int id);

    void addPlayerToLobby(int n);

    ~LobbyHostWidget();

private:
    void onClickStart();

    void onClickCancel();
};

#endif
