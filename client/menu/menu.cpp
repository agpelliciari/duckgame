#include "menu.h"

#include "ui_menu.h"

Menu::Menu(MenuHandler& handler): ui(new Ui::Menu), handler(handler) {
    ui->setupUi(this);

    initializeTimerForActions();

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

void Menu::startLobby() { this->close(); }

Menu::~Menu() { delete ui; }

void Menu::mountSetHostnamePort() {
    SetHostnamePortHandler setHostnamePortHandler{
            .onClickContinue =
                    [this](const std::string& hostname, const std::string& port) {
                        handler.onSetHostnamePort(hostname, port);
                        unMountWidget();
                        mountCreateJoin();
                    },
            .onClickQuit = [this] { this->close(); },
    };
    SetHostnamePortWidget* setHostnamePortWidget =
            new SetHostnamePortWidget(setHostnamePortHandler, ui->centralwidget);
    mountWidget(setHostnamePortWidget);
}

void Menu::mountCreateJoin() {
    CreateJoinHandler createJoinHandler{
            .onClickCreateGame =
                    [this] {
                        unMountWidget();
                        mountSetSoloDuoHost();
                    },
            .onClickJoinGame =
                    [this] {
                        unMountWidget();
                        mountSetSoloDuoGuest();
                    },
            .onClickQuit = [this] { this->close(); },
    };
    CreateJoinWidget* createJoinWidget = new CreateJoinWidget(createJoinHandler, ui->centralwidget);
    mountWidget(createJoinWidget);
}

void Menu::mountSetLobbyIdForSolo() {
    SetLobbyIdHandler setLobbyIdHandler{.onClickJoin =
                                                [this](int lobbyId) {
                                                    handler.onJoinSoloLobby(lobbyId);
                                                    unMountWidget();
                                                    mountLobbyGuest();
                                                    addPlayerToLobby(1);
                                                    addPlayerToLobby(2);
                                                },
                                        .onClickCancel =
                                                [this] {
                                                    unMountWidget();
                                                    mountSetSoloDuoGuest();
                                                }};
    mountSetLobbyId(setLobbyIdHandler);
}

void Menu::mountSetLobbyIdForDuo() {
    SetLobbyIdHandler setLobbyIdHandler{.onClickJoin =
                                                [this](int lobbyId) {
                                                    handler.onJoinDuoLobby(lobbyId);
                                                    unMountWidget();
                                                    mountLobbyGuest();
                                                    addPlayerToLobby(1);
                                                    addPlayerToLobby(2);
                                                },
                                        .onClickCancel =
                                                [this] {
                                                    unMountWidget();
                                                    mountSetSoloDuoGuest();
                                                }};
    mountSetLobbyId(setLobbyIdHandler);
}

void Menu::mountSetLobbyId(SetLobbyIdHandler setLobbyIdHandler) {
    SetLobbyIdWidget* setLobbyIdWidget = new SetLobbyIdWidget(setLobbyIdHandler, ui->centralwidget);
    mountWidget(setLobbyIdWidget);
}

void Menu::mountSetSoloDuoHost() {
    SetSoloDuoHandler setSoloDuoHandler{.onClickSolo =
                                                [this] {
                                                    handler.onCreateSoloLobby();
                                                    unMountWidget();
                                                    mountLobbyHost();
                                                    addPlayerToLobby(1);
                                                },
                                        .onClickDuo =
                                                [this] {
                                                    handler.onCreateDuoLobby();
                                                    unMountWidget();
                                                    mountLobbyHost();
                                                    addPlayerToLobby(1);
                                                    addPlayerToLobby(2);
                                                },
                                        .onClickCancel =
                                                [this] {
                                                    unMountWidget();
                                                    mountCreateJoin();
                                                }};
    mountSetSoloDuo(setSoloDuoHandler);
}

void Menu::mountSetSoloDuoGuest() {
    SetSoloDuoHandler setSoloDuoHandler{.onClickSolo =
                                                [this] {
                                                    unMountWidget();
                                                    mountSetLobbyIdForSolo();
                                                },
                                        .onClickDuo =
                                                [this] {
                                                    unMountWidget();
                                                    mountSetLobbyIdForDuo();
                                                },
                                        .onClickCancel =
                                                [this] {
                                                    unMountWidget();
                                                    mountCreateJoin();
                                                }};
    mountSetSoloDuo(setSoloDuoHandler);
}

void Menu::mountSetSoloDuo(SetSoloDuoHandler setSoloDuoHandler) {
    SetSoloDuoWidget* setSoloDuoWidget = new SetSoloDuoWidget(setSoloDuoHandler, ui->centralwidget);
    mountWidget(setSoloDuoWidget);
}

void Menu::mountLobbyHost() {
    LobbyHostHandler lobbyHostHandler{.onClickStart = [this] { handler.onStartLobby("Mapa 1"); },
                                      .onClickCancel =
                                              [this] {
                                                  unMountWidget();
                                                  mountSetSoloDuoHost();
                                              }};
    LobbyHostWidget* lobbyHostWidget = new LobbyHostWidget(lobbyHostHandler, ui->centralwidget);
    mountWidget(lobbyHostWidget);
}

void Menu::mountLobbyGuest() {
    LobbyGuestHandler lobbyGuestHandler{.onClickCancel = [this] {
        unMountWidget();
        mountSetSoloDuoGuest();
    }};
    LobbyGuestWidget* lobbyGuestWidget = new LobbyGuestWidget(lobbyGuestHandler, ui->centralwidget);
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

void Menu::initializeTimerForActions() {
    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [this]() {
        loadActionsBuffer();
        processActionsBuffer();
    });
    timer->start(1000);
}

void Menu::loadActionsBuffer() {
    MenuAction actionToBuffer;
    while (handler.tryPopActionToMenu(actionToBuffer)) {
        buffer.push(actionToBuffer);
    }
}

void Menu::processActionsBuffer() {
    while (not buffer.empty()) {
        MenuAction action = buffer.front();
        buffer.pop();
        action.exec(*this);
    }
}
