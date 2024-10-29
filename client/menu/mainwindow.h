#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "setHostnamePortWidget/setHostnamePortWidget.h"
#include "createJoinWidget/createJoinWidget.h"
#include "setLobbyIdWidget/setLobbyIdWidget.h"
#include "setSoloDuoWidget/setSoloDuoWidget.h"
#include "lobbyWidget/lobbyHostWidget/lobbyHostWidget.h"
#include "lobbyWidget/lobbyGuestWidget/lobbyGuestWidget.h"

#include <QMainWindow>
#include <functional>

struct menuHandler {
    std::function<void(uint8_t playercount)> onClickCreateLobby;
    std::function<void(uint8_t playercount, unsigned int idlobby)> onClickJoinLobby;
};

QT_BEGIN_NAMESPACE
namespace Ui {
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

private:
    Ui::MainWindow *ui;
    menuHandler handler;

public:
    MainWindow(menuHandler handler);

    void updateIdDisplayedInLobby(int id);

    ~MainWindow();

private:
    void mountSetHostnamePort();

    void mountCreateJoin();

    void mountSetLobbyId();

    void mountSetSoloDuoHost();

    void mountSetSoloDuoGuest();

    void mountSetSoloDuo(SetSoloDuoHandler handler);

    void mountLobbyHost();

    void mountLobbyGuest();

    void mountWidget(QWidget* widget);

    void unMountWidget();
};
#endif
