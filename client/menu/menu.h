#ifndef MENU_H
#define MENU_H

#include <QMainWindow>
#include <functional>
#include <string>

#include "./menuhandler.h"
#include "createJoinWidget/createJoinWidget.h"
#include "lobbyWidget/lobbyGuestWidget/lobbyGuestWidget.h"
#include "lobbyWidget/lobbyHostWidget/lobbyHostWidget.h"
#include "setHostnamePortWidget/setHostnamePortWidget.h"
#include "setLobbyIdWidget/setLobbyIdWidget.h"
#include "setSoloDuoWidget/setSoloDuoWidget.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Menu;
}
QT_END_NAMESPACE

class Menu: public QMainWindow {
    Q_OBJECT

private:
    Ui::Menu* ui;          // cppcheck-suppress unusedStructMember
    MenuHandler& handler;  // cppcheck-suppress unusedStructMember

public:
    explicit Menu(MenuHandler& handler);

    void updateIdDisplayedInLobby(int id);

    void addPlayerToLobby(int n);

    ~Menu();

private:
    void mountSetHostnamePort();

    void mountCreateJoin();

    void mountSetLobbyId();

    void mountSetSoloDuoHost();

    void mountSetSoloDuoGuest();

    void mountSetSoloDuo(SetSoloDuoHandler setSoloDuoHandler);

    void mountLobbyHost();

    void mountLobbyGuest();

    void mountWidget(QWidget* widget);

    void unMountWidget();
};
#endif
