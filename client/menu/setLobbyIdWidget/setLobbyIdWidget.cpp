#include "setLobbyIdWidget.h"

#include <iostream>  // TODO remove

#include "ui_setLobbyIdWidget.h"

SetLobbyIdWidget::SetLobbyIdWidget(const SetLobbyIdHandler& handler, QWidget* parent):
        QWidget(parent), ui(new Ui::SetLobbyIdWidget), handler(handler) {
    ui->setupUi(this);

    connect(ui->joinButton, &QPushButton::clicked, this, &SetLobbyIdWidget::onClickJoin);
    connect(ui->cancelButton, &QPushButton::clicked, this, &SetLobbyIdWidget::onClickCancel);
}

SetLobbyIdWidget::~SetLobbyIdWidget() { delete ui; }

void SetLobbyIdWidget::onClickJoin() {
    QString lobbyIdInputText = ui->lobbyIdInput->text();

    bool ok;
    int lobbyId = lobbyIdInputText.toInt(&ok);

    if (!ok) {
        std::cout << "El ID de lobby ingresado no es un numero valido" << std::endl;  // TODO remove
        return;
    }

    if (handler.onClickJoin)
        handler.onClickJoin(lobbyId);
}

void SetLobbyIdWidget::onClickCancel() {
    if (handler.onClickCancel)
        handler.onClickCancel();
}
