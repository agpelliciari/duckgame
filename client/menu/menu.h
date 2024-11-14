#ifndef MENU_H
#define MENU_H

#include <QMainWindow>
#include <QTimer>
#include <functional>
#include <string>

#include "./menuhandler.h"
#include "common/queue.h"
#include "createJoinWidget/createJoinWidget.h"
#include "lobbyWidget/lobbyGuestWidget/lobbyGuestWidget.h"
#include "lobbyWidget/lobbyHostWidget/lobbyHostWidget.h"
#include "notificationWidget/notificationWidget.h"
#include "setHostnamePortWidget/setHostnamePortWidget.h"
#include "setLobbyIdWidget/setLobbyIdWidget.h"
#include "setSoloDuoWidget/setSoloDuoWidget.h"

#include "menuAction.h"

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

    std::queue<MenuAction> buffer;  // cppcheck-suppress unusedStructMember
    QWidget* currentWidget = nullptr;
    QWidget* currentNotification = nullptr;

public:
    explicit Menu(MenuHandler& handler);

    void updateIdDisplayedInLobby(int id);

    void updateMapsDisplayedInLobby(const std::vector<std::string>& maps);

    void displayNotification(const std::string& label);

    void addPlayerToLobby();

    void removePlayerFromLobby();

    void reset();

    void startLobby();

    ~Menu();

private:
    void mountSetHostnamePort();

    void mountCreateJoin();

    void mountSetLobbyIdForSolo();

    void mountSetLobbyIdForDuo();

    void mountSetLobbyId(SetLobbyIdHandler setLobbyIdHandler);

    void mountSetSoloDuoHost();

    void mountSetSoloDuoGuest();

    void mountSetSoloDuo(SetSoloDuoHandler setSoloDuoHandler);

    void mountLobbyHost();

    void mountLobbyGuest();

    void mountWidget(QWidget* widget);

    void unMountWidget();

    void mountNotification(NotificationWidget* notification);

    void unMountNotification();

    void initializeTimerForActions();

    void loadActionsBuffer();

    void processActionsBuffer();
};
#endif
