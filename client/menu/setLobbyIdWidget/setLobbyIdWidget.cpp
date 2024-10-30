#include "setLobbyIdWidget.h"

#include "ui_setLobbyIdWidget.h"

SetLobbyIdWidget::SetLobbyIdWidget(const SetLobbyIdHandler& handler, QWidget* parent):
        QWidget(parent), ui(new Ui::SetLobbyIdWidget), handler(handler) {
    ui->setupUi(this);

    connect(ui->joinButton, &QPushButton::clicked, this, &SetLobbyIdWidget::onClickJoin);
    connect(ui->cancelButton, &QPushButton::clicked, this, &SetLobbyIdWidget::onClickCancel);
}

SetLobbyIdWidget::~SetLobbyIdWidget() { delete ui; }

void SetLobbyIdWidget::onClickJoin() {
    if (handler.onClickJoin)
        handler.onClickJoin();
}

void SetLobbyIdWidget::onClickCancel() {
    if (handler.onClickCancel)
        handler.onClickCancel();
}
