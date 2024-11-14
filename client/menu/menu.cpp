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

void Menu::updateMapsDisplayedInLobby(const std::vector<std::string>& maps) {
    QVBoxLayout* layout = qobject_cast<QVBoxLayout*>(ui->centralwidget->layout());

    if (layout->count() == 0)
        throw std::runtime_error("There is no widget mounted");

    QWidget* widget = layout->itemAt(0)->widget();
    if (auto* lobbyHostWidget = qobject_cast<LobbyHostWidget*>(widget)) {
        lobbyHostWidget->updateMapsDisplayedInLobby(maps);
    }
}

void Menu::displayNotification(const std::string& label) {
    NotificationHandler notificationHandler{.label = label,
                                            .onClose = [this] { unMountNotification(); }};
    NotificationWidget* notificationWidget =
            new NotificationWidget(notificationHandler, ui->centralwidget);

    mountNotification(notificationWidget);
}

void Menu::addPlayerToLobby() {
    QVBoxLayout* layout = qobject_cast<QVBoxLayout*>(ui->centralwidget->layout());

    if (layout->count() == 0)
        throw std::runtime_error("There is no widget mounted");

    QWidget* widget = layout->itemAt(0)->widget();
    if (auto* lobbyHostWidget = qobject_cast<LobbyHostWidget*>(widget)) {
        lobbyHostWidget->addPlayerToLobby();
    } else if (auto* lobbyGuestWidget = qobject_cast<LobbyGuestWidget*>(widget)) {
        lobbyGuestWidget->addPlayerToLobby();
    }
}

void Menu::removePlayerFromLobby() {
    QVBoxLayout* layout = qobject_cast<QVBoxLayout*>(ui->centralwidget->layout());

    if (layout->count() == 0)
        throw std::runtime_error("There is no widget mounted");

    QWidget* widget = layout->itemAt(0)->widget();
    if (auto* lobbyHostWidget = qobject_cast<LobbyHostWidget*>(widget)) {
        lobbyHostWidget->removePlayerFromLobby();
    } else if (auto* lobbyGuestWidget = qobject_cast<LobbyGuestWidget*>(widget)) {
        lobbyGuestWidget->removePlayerFromLobby();
    }
}

void Menu::reset() {
    unMountWidget();
    mountCreateJoin();
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
                                                },
                                        .onClickDuo =
                                                [this] {
                                                    handler.onCreateDuoLobby();
                                                    unMountWidget();
                                                    mountLobbyHost();
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
    LobbyHostHandler lobbyHostHandler{.onClickStart = [this](const std::string& selectedMap) { handler.onStartLobby(selectedMap); },
                                      .onClickCancel =
                                              [this] {
                                                  handler.onCancelLobby();
                                                  unMountWidget();
                                                  mountSetSoloDuoHost();
                                              }};
    LobbyHostWidget* lobbyHostWidget = new LobbyHostWidget(lobbyHostHandler, ui->centralwidget);
    mountWidget(lobbyHostWidget);
}

void Menu::mountLobbyGuest() {
    LobbyGuestHandler lobbyGuestHandler{.onClickCancel = [this] {
        handler.onCancelLobby();
        unMountWidget();
        mountSetSoloDuoGuest();
    }};
    LobbyGuestWidget* lobbyGuestWidget = new LobbyGuestWidget(lobbyGuestHandler, ui->centralwidget);
    mountWidget(lobbyGuestWidget);
}

void Menu::mountWidget(QWidget* widget) {
    if (currentWidget != nullptr)
        throw std::runtime_error("A widget is already mounted");

    if (currentNotification != nullptr)
        unMountNotification();

    QVBoxLayout* layout = qobject_cast<QVBoxLayout*>(ui->centralwidget->layout());
    layout->addWidget(widget);
    currentWidget = widget;
}

void Menu::unMountWidget() {
    if (currentWidget == nullptr)
        throw std::runtime_error("There is no widget to unmount");

    QVBoxLayout* layout = qobject_cast<QVBoxLayout*>(ui->centralwidget->layout());
    layout->removeWidget(currentWidget);
    currentWidget->deleteLater();
    currentWidget = nullptr;
}

void Menu::mountNotification(NotificationWidget* notification) {
    if (currentNotification != nullptr)
        unMountNotification();

    QVBoxLayout* layout = qobject_cast<QVBoxLayout*>(ui->centralwidget->layout());
    layout->insertWidget(0, notification);
    currentNotification = notification;
}

void Menu::unMountNotification() {
    if (currentNotification == nullptr)
        return;

    QVBoxLayout* layout = qobject_cast<QVBoxLayout*>(ui->centralwidget->layout());
    layout->removeWidget(currentNotification);
    currentNotification->deleteLater();
    currentNotification = nullptr;
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
