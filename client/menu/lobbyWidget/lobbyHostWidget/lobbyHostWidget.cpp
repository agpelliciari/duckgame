#include "lobbyHostWidget.h"
#include "ui_lobbyHostWidget.h"

LobbyHostWidget::LobbyHostWidget(const LobbyHostHandler &handler, QWidget *parent) : QWidget(parent), ui(new Ui::LobbyHostWidget), handler(handler) {
    ui->setupUi(this);

    connect(ui->startButton, &QPushButton::clicked, this, &LobbyHostWidget::onClickStart);
    connect(ui->cancelButton, &QPushButton::clicked, this, &LobbyHostWidget::onClickCancel);
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