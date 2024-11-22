#include "interface.h"
#include "ui_interface.h"

Interface::Interface(const InterfaceHandler& handler, QWidget* parent): QWidget(parent), ui(new Ui::Interface), handler(handler) {
    ui->setupUi(this);

    initializePreview();

    ui->alertLabel->setWordWrap(true);
    ui->alertFrame->setVisible(false);

    setUpButton(ui->exportButton, QString(DATA_PATH) + SAVE_ICON_SOURCE, &Interface::onClickExport);
    setUpButton(ui->importButton, QString(DATA_PATH) + LOAD_ICON_SOURCE, &Interface::onClickImport);

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

void Interface::displayNotificationError(const std::string& label) {
    ui->alertFrame->setStyleSheet("background-color: #d32f2f; border: 1px solid #f44336;");
    ui->alertLabel->setStyleSheet("border: 0px solid; color: white;");
    displayNotification(label);
}

void Interface::displayNotificationSuccess(const std::string& label) {
    ui->alertFrame->setStyleSheet("background-color: #388e3c; border: 1px solid #66bb6a;");
    ui->alertLabel->setStyleSheet("border: 0px solid; color: white;");
    displayNotification(label);
}

void Interface::displayNotification(const std::string& label) {
    ui->alertLabel->setText(QString::fromStdString(label));
    ui->alertFrame->setVisible(true);
    

    QTimer::singleShot(4000, this, [this]() {
        ui->alertFrame->setVisible(false);
    });
}

Interface::~Interface() {
    delete ui;
}

void Interface::onClickExport() {
    handler.onExport();
}

void Interface::onClickImport() {
    handler.onImport();
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
    ui->previewView->scale(3.0, 3.0);
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

void Interface::setUpButton(QPushButton* button, const QString& iconPath, void (Interface::*method)()) {
    connect(button, &QPushButton::clicked, this, method);
    QIcon icon(iconPath);
    button->setIcon(icon);
    button->setIconSize(QSize(16, 16));
    button->setStyleSheet("text-align: center;");
}