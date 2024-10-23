#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "client/client.h"

QT_BEGIN_NAMESPACE
namespace Ui {
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT
private:
    Client& client;
    Ui::MainWindow *ui;

public:
    MainWindow(Client& _client, QWidget *parent = nullptr);

    ~MainWindow();

private:
    void onClickCreateLobby();

    void onClickJoinLobby();

    void onClickQuit();
};
#endif
