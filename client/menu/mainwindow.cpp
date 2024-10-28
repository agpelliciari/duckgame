#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(menuHandler handler): ui(new Ui::MainWindow), handler(handler) {
    ui->setupUi(this);
    mountCreateJoin();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::mountCreateJoin() {
    QVBoxLayout* layout = qobject_cast<QVBoxLayout*>(ui->centralwidget->layout());

    CreateJoinHandler handler;
    handler.onClickCreateGame = [this]() {
        unMountWidget();
        mountSetSoloDuo();
    };

    handler.onClickJoinGame = [this]() {
        unMountWidget();
        mountSetLobbyId();
    };

    handler.onClickQuit = [this]() {
        this->close();
    };

    CreateJoinWidget* createJoinWidget = new CreateJoinWidget(handler, ui->centralwidget);
    layout->insertWidget(0, createJoinWidget);
}

void MainWindow::mountSetLobbyId() {
    QVBoxLayout* layout = qobject_cast<QVBoxLayout*>(ui->centralwidget->layout());

    SetLobbyIdHandler handler;

    handler.onClickJoin = []() {
    };

    handler.onClickCancel = [this]() {
        unMountWidget();
        mountCreateJoin();
    };

    SetLobbyIdWidget* setLobbyIdWidget = new SetLobbyIdWidget(handler, ui->centralwidget);
    layout->insertWidget(0, setLobbyIdWidget);
}

void MainWindow::mountSetSoloDuo() {
    QVBoxLayout* layout = qobject_cast<QVBoxLayout*>(ui->centralwidget->layout());

    SetSoloDuoHandler handler;

    handler.onClickSolo = []() {
    };

    handler.onClickDuo = []() {
    };

    handler.onClickCancel = [this]() {
        unMountWidget();
        mountCreateJoin();
    };

    SetSoloDuoWidget* setSoloDuoWidget = new SetSoloDuoWidget(handler, ui->centralwidget);
    layout->insertWidget(0, setSoloDuoWidget);
}

void MainWindow::unMountWidget() {
    QVBoxLayout* layout = qobject_cast<QVBoxLayout*>(ui->centralwidget->layout());

    if (layout && layout->count() > 0) {
        QWidget* widget = layout->itemAt(0)->widget();
        if (widget) {
            layout->removeWidget(widget);
            delete widget;
        }
    }
}