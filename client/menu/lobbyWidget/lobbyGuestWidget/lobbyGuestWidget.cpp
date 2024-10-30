#include "lobbyGuestWidget.h"

#include "ui_lobbyGuestWidget.h"

LobbyGuestWidget::LobbyGuestWidget(const LobbyGuestHandler& handler, QWidget* parent):
        QWidget(parent), ui(new Ui::LobbyGuestWidget), handler(handler) {
    ui->setupUi(this);

    connect(ui->cancelButton, &QPushButton::clicked, this, &LobbyGuestWidget::onClickCancel);
}

void LobbyGuestWidget::updateIdDisplayedInLobby(int id) {
    ui->lobbyIDLabel->setText(QString("Lobby ID: %1").arg(id));
}

void LobbyGuestWidget::addPlayerToLobby(int n) {
    QVBoxLayout* layout = qobject_cast<QVBoxLayout*>(ui->players->layout());
    PlayerWidget* player = new PlayerWidget(n, ui->players);
    layout->addWidget(player);
}

LobbyGuestWidget::~LobbyGuestWidget() { delete ui; }

void LobbyGuestWidget::onClickCancel() {
    if (handler.onClickCancel)
        handler.onClickCancel();
}
