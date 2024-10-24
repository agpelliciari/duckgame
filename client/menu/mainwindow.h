#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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

class MainWindow: public QMainWindow {
    Q_OBJECT

private:
    Ui::MainWindow* ui;   // cppcheck-suppress unusedStructMember
    menuHandler handler;  // cppcheck-suppress unusedStructMember

public:
    explicit MainWindow(menuHandler handler);

    ~MainWindow();

private:
    void onClickCreateLobby();

    void onClickJoinLobby();

    void onClickQuit();
};
#endif
