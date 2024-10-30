#include "setHostnamePortWidget.h"
#include "ui_setHostnamePortWidget.h"

SetHostnamePortWidget::SetHostnamePortWidget(const SetHostnamePortHandler &handler, QWidget *parent) : QWidget(parent), ui(new Ui::SetHostnamePortWidget), handler(handler) {
    ui->setupUi(this);

    connect(ui->continueButton, &QPushButton::clicked, this, &SetHostnamePortWidget::onClickContinue);
    connect(ui->quitButton, &QPushButton::clicked, this, &SetHostnamePortWidget::onClickQuit);
}

SetHostnamePortWidget::~SetHostnamePortWidget() {
    delete ui;
}

void SetHostnamePortWidget::onClickContinue() {
    QString hostname = ui->hostnameTextInput->text();
    QString port = ui->portTextInput->text();
    // TODO: validar
    if (handler.onClickContinue)
        handler.onClickContinue(hostname.toStdString(), port.toStdString());
}

void SetHostnamePortWidget::onClickQuit() {
    if (handler.onClickQuit) handler.onClickQuit();
}