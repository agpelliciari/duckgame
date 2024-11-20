#include "interface.h"
#include "ui_interface.h"

Interface::Interface(const InterfaceHandler& handler, QWidget* parent): QWidget(parent), ui(new Ui::Interface), handler(handler) {
    ui->setupUi(this);

    initializePreview();

    connect(ui->exportButton, &QPushButton::clicked, this, &Interface::onClickExport);
    connect(ui->editorModeDropdown, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, &Interface::onEditorModeDropdownChangedInt);
    connect(ui->selectorDropdown, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, &Interface::onSelectorDropdownIndexChanged);
}

void Interface::setEditorModeDropdownOptions(std::vector<std::string> names) {
    setDropdownOptions(names, ui->editorModeDropdown);
}

void Interface::setSelectorDropdownOptions(std::vector<std::string> names) {
    setDropdownOptions(names, ui->selectorDropdown);
}

void Interface::selectorDropdownIndexChanged(size_t index) {
    ui->selectorDropdown->blockSignals(true);
    ui->selectorDropdown->setCurrentIndex(index);
    ui->selectorDropdown->blockSignals(false);
}

void Interface::displayNoneOnPreview() {
    preview->setBrush(Qt::NoBrush);
}

void Interface::displayMapObjectOnPreview(Texture texture) {
    QBrush brush(texture.pixelMap);
    preview->setBrush(brush);
}

Interface::~Interface() {
    delete ui;
}

void Interface::onClickExport() {
    handler.onExport();
}

void Interface::onEditorModeDropdownChangedInt(int index) {
    MapObjectType mode = static_cast<MapObjectType>(index);
    onEditorModeDropdownChanged(mode);
}

void Interface::onEditorModeDropdownChanged(MapObjectType mode) {
    handler.onEditorModeDropdownChanged(mode);
}

void Interface::onSelectorDropdownIndexChanged(int index) {
    handler.onSelectorDropdownIndexChanged(index);
}

void Interface::initializePreview() {
    QGraphicsScene* scene = new QGraphicsScene(this);
    ui->previewView->setScene(scene);
    ui->previewView->scale(3.0, 3.0); // TODO HARDCODED
    scene->setSceneRect(0, 0, textureSize, textureSize);
    preview = scene->addRect(0, 0, textureSize, textureSize, QPen(Qt::NoPen), Qt::NoBrush);
}

void Interface::setDropdownOptions(std::vector<std::string> options, QComboBox* dropdown) {
    bool wasEmpty = dropdown->count() == 0;

    if (!wasEmpty) {
        ui->selectorDropdown->blockSignals(true);
        ui->selectorDropdown->setCurrentIndex(0);
        while (dropdown->count() > 1) {
            dropdown->removeItem(0);
        }
    }

    QStringList qOptions;
    for (const auto& option : options)
        qOptions << QString::fromStdString(option);
    dropdown->addItems(qOptions);

    if (!wasEmpty) {
        dropdown->removeItem(0);
        ui->selectorDropdown->blockSignals(false);
    }
}