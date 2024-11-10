#include "interface.h"
#include "ui_interface.h"

Interface::Interface(const InterfaceHandler& handler, QWidget* parent): QWidget(parent), ui(new Ui::Interface), preview(new QGraphicsScene(this)), handler(handler) {
    ui->setupUi(this);

    initializePreview();

    connect(ui->exportButton, &QPushButton::clicked, this, &Interface::onClickExport);
    connect(ui->blockDropdown, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, &Interface::onBlockDropdownIndexChanged);
}

void Interface::setBlockDropdownOptions(std::vector<std::string> blockNames) {
    QStringList qBlockNames;
    for (const auto& name : blockNames) {
        qBlockNames << QString::fromStdString(name);
    }
    ui->blockDropdown->addItems(qBlockNames);
}

void Interface::blockDropdownIndexChanged(size_t index) {
    ui->blockDropdown->setCurrentIndex(index);
}

void Interface::displayOnPreview(QBrush texture) {
    block->setBrush(texture);
}

Interface::~Interface() {
    delete ui;
}

void Interface::onClickExport() {
    handler.onExport();
}

void Interface::initializePreview() {
    int blockSize = 32; // TODO CONSTANTE
    ui->previewView->setScene(preview);
    preview->setSceneRect(0, 0, blockSize, blockSize);
    block = preview->addRect(0, 0, blockSize, blockSize, QPen(Qt::NoPen), Qt::NoBrush);
}

void Interface::onBlockDropdownIndexChanged(int index) {
    handler.onBlockDropdownIndexChanged(index);
}