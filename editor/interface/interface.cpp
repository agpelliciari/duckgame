#include "interface.h"
#include "ui_interface.h"

Interface::Interface(const InterfaceHandler& handler, QWidget* parent): QWidget(parent), ui(new Ui::Interface), preview(new QGraphicsScene(this)), handler(handler) {
    ui->setupUi(this);

    initializePreview();

    connect(ui->exportButton, &QPushButton::clicked, this, &Interface::onClickExport);
    connect(ui->backgroundDropdown, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, &Interface::onBackgroundDropdownIndexChanged);
    connect(ui->blockDropdown, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, &Interface::onBlockDropdownIndexChanged);
}

void Interface::setBackgroundDropdownOptions(std::vector<std::string> backgroundNames) {
    QStringList qBackgroundNames;
    for (const auto& name : backgroundNames)
        qBackgroundNames << QString::fromStdString(name);
    ui->backgroundDropdown->addItems(qBackgroundNames);
}

void Interface::setBlockDropdownOptions(std::vector<std::string> blockNames) {
    QStringList qBlockNames;
    for (const auto& name : blockNames)
        qBlockNames << QString::fromStdString(name);
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
    int blockSize = 16; // TODO CONSTANTE
    ui->previewView->setScene(preview);
    preview->setSceneRect(0, 0, blockSize, blockSize);
    block = preview->addRect(0, 0, blockSize, blockSize, QPen(Qt::NoPen), Qt::NoBrush);
}

void Interface::onBackgroundDropdownIndexChanged(int index) {
    handler.onBackgroundDropdownIndexChanged(index);
}

void Interface::onBlockDropdownIndexChanged(int index) {
    handler.onBlockDropdownIndexChanged(index);
}