#include "interface.h"
#include "ui_interface.h"

Interface::Interface(const InterfaceHandler& handler, QWidget* parent): QWidget(parent), ui(new Ui::Interface), handler(handler) {
    ui->setupUi(this);

    initializePreview();

    connect(ui->exportButton, &QPushButton::clicked, this, &Interface::onClickExport);
    connect(ui->backgroundDropdown, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, &Interface::onBackgroundDropdownIndexChanged);
    connect(ui->blockDropdown, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, &Interface::onBlockDropdownIndexChanged);
}

void Interface::setBackgroundDropdownOptions(std::vector<std::string> backgroundNames) {
    setDropdownOptions(backgroundNames, ui->backgroundDropdown);
}

void Interface::setBlockDropdownOptions(std::vector<std::string> blockNames) {
    setDropdownOptions(blockNames, ui->blockDropdown);
}

void Interface::blockDropdownIndexChanged(size_t index) {
    ui->blockDropdown->setCurrentIndex(index);
}

void Interface::displayOnPreview(QPixmap pixelMap) {
    QBrush texture(pixelMap);
    preview->setBrush(texture);
}

Interface::~Interface() {
    delete ui;
}

void Interface::onClickExport() {
    handler.onExport();
}

void Interface::onBackgroundDropdownIndexChanged(int index) {
    handler.onBackgroundDropdownIndexChanged(index);
}

void Interface::onBlockDropdownIndexChanged(int index) {
    handler.onBlockDropdownIndexChanged(index);
}

void Interface::initializePreview() {
    QGraphicsScene* scene = new QGraphicsScene(this);
    ui->previewView->setScene(scene);
    ui->previewView->scale(3.0, 3.0); // TODO HARDCODED
    scene->setSceneRect(0, 0, textureSize, textureSize);
    preview = scene->addRect(0, 0, textureSize, textureSize, QPen(Qt::NoPen), Qt::NoBrush);
}

void Interface::setDropdownOptions(std::vector<std::string> options, QComboBox* dropdown) {
    QStringList qOptions;
    for (const auto& option : options)
        qOptions << QString::fromStdString(option);
    dropdown->addItems(qOptions);
}