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

void LobbyGuestWidget::addPlayerToLobby() {
    numberOfPlayers++;
    QVBoxLayout* layout = qobject_cast<QVBoxLayout*>(ui->players->layout());
    PlayerWidget* player = new PlayerWidget(numberOfPlayers, ui->players);
    layout->addWidget(player);
}

void LobbyGuestWidget::removePlayerFromLobby() {
    if (numberOfPlayers == 0)
        throw std::runtime_error("There is no players to remove");

    numberOfPlayers--;
    QVBoxLayout* layout = qobject_cast<QVBoxLayout*>(ui->players->layout());
    int layoutCount = layout->count();

    if (layout->count() == 0)
        throw std::runtime_error("There is no player widget to remove");

    QWidget* widget = layout->itemAt(layoutCount - 1)->widget();
    layout->removeWidget(widget);
    widget->deleteLater();
}

LobbyGuestWidget::~LobbyGuestWidget() { delete ui; }

void LobbyGuestWidget::onClickCancel() {
    if (handler.onClickCancel)
        handler.onClickCancel();
}
