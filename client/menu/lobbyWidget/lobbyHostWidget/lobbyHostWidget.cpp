#include "lobbyHostWidget.h"
#include "ui_lobbyHostWidget.h"

LobbyHostWidget::LobbyHostWidget(const LobbyHostHandler &handler, QWidget *parent) : QWidget(parent), ui(new Ui::LobbyHostWidget), handler(handler) {
    ui->setupUi(this);

    connect(ui->startButton, &QPushButton::clicked, this, &LobbyHostWidget::onClickStart);
    connect(ui->cancelButton, &QPushButton::clicked, this, &LobbyHostWidget::onClickCancel);
}

void LobbyHostWidget::updateIdDisplayedInLobby(int id) {
    ui->lobbyIDLabel->setText(QString("Lobby ID: %1").arg(id));
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