#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(menuHandler handler): ui(new Ui::MainWindow), handler(handler) {
    ui->setupUi(this);
    mountSetHostnamePort();
    ui->centralwidget->setFocus();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::mountSetHostnamePort() {
    SetHostnamePortHandler handler {
        .onClickContinue = [this] { unMountWidget(); mountCreateJoin(); },
        .onClickQuit = [this] { this->close(); },
    };

    QVBoxLayout* layout = qobject_cast<QVBoxLayout*>(ui->centralwidget->layout());
    SetHostnamePortWidget* setHostnamePortWidget = new SetHostnamePortWidget(handler, ui->centralwidget);
    layout->insertWidget(0, setHostnamePortWidget);
}

void MainWindow::mountCreateJoin() {
    CreateJoinHandler handler {
        .onClickCreateGame = [this] { unMountWidget(); mountSetSoloDuoHost(); },
        .onClickJoinGame = [this] { unMountWidget(); mountSetLobbyId(); },
        .onClickQuit = [this] { this->close(); },
    };

    QVBoxLayout* layout = qobject_cast<QVBoxLayout*>(ui->centralwidget->layout());
    CreateJoinWidget* createJoinWidget = new CreateJoinWidget(handler, ui->centralwidget);
    layout->insertWidget(0, createJoinWidget);
}

void MainWindow::mountSetLobbyId() {
    SetLobbyIdHandler handler {
        .onClickJoin = [this] { unMountWidget(); mountSetSoloDuoGuest(); },
        .onClickCancel = [this] { unMountWidget(); mountCreateJoin(); }
    };

    QVBoxLayout* layout = qobject_cast<QVBoxLayout*>(ui->centralwidget->layout());
    SetLobbyIdWidget* setLobbyIdWidget = new SetLobbyIdWidget(handler, ui->centralwidget);
    layout->insertWidget(0, setLobbyIdWidget);
}

void MainWindow::mountSetSoloDuoHost() {
    SetSoloDuoHandler handler {
        .onClickSolo = [this] { unMountWidget(); mountLobbyHost(); },
        .onClickDuo = [this] { unMountWidget(); mountLobbyHost(); },
        .onClickCancel = [this] { unMountWidget(); mountCreateJoin(); }
    };
    mountSetSoloDuo(handler);
}

void MainWindow::mountSetSoloDuoGuest() {
    SetSoloDuoHandler handler {
        .onClickSolo = [this] { unMountWidget(); mountLobbyGuest(); },
        .onClickDuo = [this] { unMountWidget(); mountLobbyGuest(); },
        .onClickCancel = [this] { unMountWidget(); mountSetLobbyId(); }
    };
    mountSetSoloDuo(handler);
}

void MainWindow::mountSetSoloDuo(SetSoloDuoHandler handler) {
    QVBoxLayout* layout = qobject_cast<QVBoxLayout*>(ui->centralwidget->layout());
    SetSoloDuoWidget* setSoloDuoWidget = new SetSoloDuoWidget(handler, ui->centralwidget);
    layout->insertWidget(0, setSoloDuoWidget);
}

void MainWindow::mountLobbyHost() {
    LobbyHostHandler handler {
        .onClickStart = [this] {},
        .onClickCancel = [this] { unMountWidget(); mountSetSoloDuoHost(); }
    };

    QVBoxLayout* layout = qobject_cast<QVBoxLayout*>(ui->centralwidget->layout());
    LobbyHostWidget* lobbyHostWidget = new LobbyHostWidget(handler, ui->centralwidget);
    layout->insertWidget(0, lobbyHostWidget);
}

void MainWindow::mountLobbyGuest() {
    LobbyGuestHandler handler {
        .onClickCancel = [this] { unMountWidget(); mountSetSoloDuoGuest(); }
    };

    QVBoxLayout* layout = qobject_cast<QVBoxLayout*>(ui->centralwidget->layout());
    LobbyGuestWidget* lobbyGuestWidget = new LobbyGuestWidget(handler, ui->centralwidget);
    layout->insertWidget(0, lobbyGuestWidget);
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