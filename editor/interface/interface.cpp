#include "interface.h"
#include "ui_interface.h"

Interface::Interface(const InterfaceHandler& handler, QWidget* parent): QWidget(parent), ui(new Ui::Interface), handler(handler) {
    ui->setupUi(this);

    connect(ui->exportButton, &QPushButton::clicked, this, &Interface::onClickExport);
}

Interface::~Interface() {
    delete ui;
}

void Interface::onClickExport() {
    if (handler.onExport)
        handler.onExport();
}