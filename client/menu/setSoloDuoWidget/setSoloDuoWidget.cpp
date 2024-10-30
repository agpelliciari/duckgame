#include "setSoloDuoWidget.h"
#include "ui_setSoloDuoWidget.h"

SetSoloDuoWidget::SetSoloDuoWidget(const SetSoloDuoHandler &handler, QWidget *parent) : QWidget(parent), ui(new Ui::SetSoloDuoWidget), handler(handler) {
    ui->setupUi(this);

    connect(ui->soloButton, &QPushButton::clicked, this, &SetSoloDuoWidget::onClickSolo);
    connect(ui->duoButton, &QPushButton::clicked, this, &SetSoloDuoWidget::onClickDuo);
    connect(ui->cancelButton, &QPushButton::clicked, this, &SetSoloDuoWidget::onClickCancel);
}

SetSoloDuoWidget::~SetSoloDuoWidget() {
    delete ui;
}

void SetSoloDuoWidget::onClickSolo() {
    if (handler.onClickSolo) handler.onClickSolo();
}

void SetSoloDuoWidget::onClickDuo() {
    if (handler.onClickDuo) handler.onClickDuo();
}

void SetSoloDuoWidget::onClickCancel() {
    if (handler.onClickCancel) handler.onClickCancel();
}