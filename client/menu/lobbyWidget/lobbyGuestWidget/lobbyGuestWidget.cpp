#include "lobbyGuestWidget.h"
#include "ui_lobbyGuestWidget.h"

LobbyGuestWidget::LobbyGuestWidget(const LobbyGuestHandler &handler, QWidget *parent) : QWidget(parent), ui(new Ui::LobbyGuestWidget), handler(handler) {
    ui->setupUi(this);

    connect(ui->cancelButton, &QPushButton::clicked, this, &LobbyGuestWidget::onClickCancel);
}

LobbyGuestWidget::~LobbyGuestWidget() {
    delete ui;
}

void LobbyGuestWidget::onClickCancel() {
    if (handler.onClickCancel) handler.onClickCancel();
}