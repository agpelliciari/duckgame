#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <functional>

#include "client/menuhandler.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow: public QMainWindow {
    Q_OBJECT

private:
    Ui::MainWindow* ui;    // cppcheck-suppress unusedStructMember
    MenuHandler& handler;  // cppcheck-suppress unusedStructMember

public:
    explicit MainWindow(MenuHandler& handler);

    ~MainWindow();

private:
    void onClickCreateLobby();

    void onClickJoinLobby();

    void onClickQuit();
};
#endif
