#include "menu.h"

#include "ui_menu.h"

Menu::Menu(MenuHandler& handler): ui(new Ui::Menu), handler(handler) {
    ui->setupUi(this);
    mountSetHostnamePort();
    ui->centralwidget->setFocus();
}

void Menu::updateIdDisplayedInLobby(int id) {
    QVBoxLayout* layout = qobject_cast<QVBoxLayout*>(ui->centralwidget->layout());

    if (layout->count() == 0)
        throw std::runtime_error("There is no widget mounted");

    QWidget* widget = layout->itemAt(0)->widget();
    if (auto* lobbyHostWidget = qobject_cast<LobbyHostWidget*>(widget)) {
        lobbyHostWidget->updateIdDisplayedInLobby(id);
    } else if (auto* lobbyGuestWidget = qobject_cast<LobbyGuestWidget*>(widget)) {
        lobbyGuestWidget->updateIdDisplayedInLobby(id);
    }
}

void Menu::addPlayerToLobby(int n) {
    QVBoxLayout* layout = qobject_cast<QVBoxLayout*>(ui->centralwidget->layout());

    if (layout->count() == 0)
        throw std::runtime_error("There is no widget mounted");

    QWidget* widget = layout->itemAt(0)->widget();
    if (auto* lobbyHostWidget = qobject_cast<LobbyHostWidget*>(widget)) {
        lobbyHostWidget->addPlayerToLobby(n);
    } else if (auto* lobbyGuestWidget = qobject_cast<LobbyGuestWidget*>(widget)) {
        lobbyGuestWidget->addPlayerToLobby(n);
    }
}

Menu::~Menu() { delete ui; }

void Menu::mountSetHostnamePort() {
    SetHostnamePortHandler handler {
        .onClickContinue = [this](std::string hostname, std::string port) {
            this->handler.setHostnamePort(hostname, port);
            unMountWidget();
            mountCreateJoin();
        },
        .onClickQuit = [this] { this->close(); },
    };
    SetHostnamePortWidget* setHostnamePortWidget = new SetHostnamePortWidget(handler, ui->centralwidget);
    mountWidget(setHostnamePortWidget);
}

void Menu::mountCreateJoin() {
    CreateJoinHandler handler {
        .onClickCreateGame = [this] { unMountWidget(); mountSetSoloDuoHost(); },
        .onClickJoinGame = [this] { unMountWidget(); mountSetLobbyId(); },
        .onClickQuit = [this] { this->close(); },
    };
    CreateJoinWidget* createJoinWidget = new CreateJoinWidget(handler, ui->centralwidget);
    mountWidget(createJoinWidget);
}

void Menu::mountSetLobbyId() {
    SetLobbyIdHandler handler {
        .onClickJoin = [this] { unMountWidget(); mountSetSoloDuoGuest(); },
        .onClickCancel = [this] { unMountWidget(); mountCreateJoin(); }
    };
    SetLobbyIdWidget* setLobbyIdWidget = new SetLobbyIdWidget(handler, ui->centralwidget);
    mountWidget(setLobbyIdWidget);
}

void Menu::mountSetSoloDuoHost() {
    SetSoloDuoHandler handler {
        .onClickSolo = [this] {
            unMountWidget();
            mountLobbyHost();
            addPlayerToLobby(1);
        },
        .onClickDuo = [this] {
            unMountWidget();
            mountLobbyHost();
            addPlayerToLobby(1);
            addPlayerToLobby(2);
        },
        .onClickCancel = [this] { unMountWidget(); mountCreateJoin(); }
    };
    mountSetSoloDuo(handler);
}

void Menu::mountSetSoloDuoGuest() {
    SetSoloDuoHandler handler {
        .onClickSolo = [this] {
            unMountWidget();
            mountLobbyGuest();
            addPlayerToLobby(1);
            addPlayerToLobby(2);
            addPlayerToLobby(3);
        },
        .onClickDuo = [this] {
            unMountWidget();
            mountLobbyGuest();
            addPlayerToLobby(1);
            addPlayerToLobby(2);
            addPlayerToLobby(3);
            addPlayerToLobby(4);
        },
        .onClickCancel = [this] { unMountWidget(); mountSetLobbyId(); }
    };
    mountSetSoloDuo(handler);
}

void Menu::mountSetSoloDuo(SetSoloDuoHandler handler) {
    SetSoloDuoWidget* setSoloDuoWidget = new SetSoloDuoWidget(handler, ui->centralwidget);
    mountWidget(setSoloDuoWidget);
}

void Menu::mountLobbyHost() {
    LobbyHostHandler handler {
        .onClickStart = [this] {},
        .onClickCancel = [this] { unMountWidget(); mountSetSoloDuoHost(); }
    };
    LobbyHostWidget* lobbyHostWidget = new LobbyHostWidget(handler, ui->centralwidget);
    mountWidget(lobbyHostWidget);
}

void Menu::mountLobbyGuest() {
    LobbyGuestHandler handler {
        .onClickCancel = [this] { unMountWidget(); mountSetSoloDuoGuest(); }
    };
    LobbyGuestWidget* lobbyGuestWidget = new LobbyGuestWidget(handler, ui->centralwidget);
    mountWidget(lobbyGuestWidget);
}

void Menu::mountWidget(QWidget* widget) {
    QVBoxLayout* layout = qobject_cast<QVBoxLayout*>(ui->centralwidget->layout());

    if (layout->count() > 0)
        throw std::runtime_error("A widget is already mounted");

    layout->insertWidget(0, widget);
}

void Menu::unMountWidget() {
    QVBoxLayout* layout = qobject_cast<QVBoxLayout*>(ui->centralwidget->layout());

    if (layout->count() == 0)
        throw std::runtime_error("There is no widget to unmount");

    QWidget* widget = layout->itemAt(0)->widget();
    layout->removeWidget(widget);
    widget->deleteLater();
}
