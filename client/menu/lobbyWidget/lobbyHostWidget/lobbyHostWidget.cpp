#include "lobbyHostWidget.h"
#include "ui_lobbyHostWidget.h"

LobbyHostWidget::LobbyHostWidget(const LobbyHostHandler &handler, QWidget *parent) : QWidget(parent), ui(new Ui::LobbyHostWidget), handler(handler) {
    ui->setupUi(this);

    ui->mapDropdown->addItem("Map 1");
    ui->mapDropdown->addItem("Map 2");
    ui->mapDropdown->addItem("Map 3");

    connect(ui->startButton, &QPushButton::clicked, this, &LobbyHostWidget::onClickStart);
    connect(ui->cancelButton, &QPushButton::clicked, this, &LobbyHostWidget::onClickCancel);
}

void LobbyHostWidget::updateIdDisplayedInLobby(int id) {
    ui->lobbyIDLabel->setText(QString("Lobby ID: %1").arg(id));
}

void LobbyHostWidget::addPlayerToLobby(int n) {
    QVBoxLayout* layout = qobject_cast<QVBoxLayout*>(ui->players->layout());
    PlayerWidget* player = new PlayerWidget(n, ui->players);
    layout->addWidget(player);
}

LobbyHostWidget::~LobbyHostWidget() {
    delete ui;
}

void LobbyHostWidget::onClickStart() {
    if (handler.onClickStart) handler.onClickStart();
}

void LobbyHostWidget::onClickCancel() {
    if (handler.onClickCancel) handler.onClickCancel();
}