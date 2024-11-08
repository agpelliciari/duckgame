#include "editorWindow.h"
#include "./ui_editorWindow.h"

#include <iostream>

EditorWindow::EditorWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::EditorWindow),
    interface(new Interface(InterfaceHandler{
        .onBackgroundDropdownIndexChanged = [this](size_t index) {
            selectedBackgroundTexture(index);
        },
        .onBlockDropdownIndexChanged = [this](size_t index) {
            selectedBlockTexture(index);
        },
        .onExport = [this]() { exportToFileSystem(); }
    }, this)),
    playground(new Playground(PlaygroundHandler{
        .onLeftClick = [this](QPoint position) {
            QPixmap texturePixmap;
            texturePixmap.load(QString::fromStdString(blocks[selectedBlockIndex].source));
            QBrush texture(texturePixmap);
            playground->addBlock(position, texture);
        },
        .onRightClick = [this](QPoint position) {
            playground->removeBlock(position);
        }
    }, this))
{
    ui->setupUi(this);

    blocks = {
        { "Nature corner-top-left", "./res/blocks/corner_top_left.png" },
        { "Nature center-top", "./res/blocks/center_top.png" },
        { "Nature corner-top-right", "./res/blocks/corner_top_right.png" },
        { "Nature center-left", "./res/blocks/center_left.png" },
        { "Nature center-center", "./res/blocks/center_center.png" },
        { "Nature center-right", "./res/blocks/center_right.png" },
        { "Nature corner-bottom-left", "./res/blocks/corner_bottom_left.png" },
        { "Nature center-bottom", "./res/blocks/center_bottom.png" },
        { "Nature corner-bottom-right", "./res/blocks/corner_bottom_right.png" },
    };

    backgrounds = {
        { "Nature Day", "./res/backgrounds/nature_day.png" },
        { "Nature Night", "./res/backgrounds/nature_night.png" },
    };

    interface->setMaximumWidth(200);
    ui->horizontalLayout->addWidget(interface);
    ui->horizontalLayout->addWidget(playground, 1);

    interface->setBackgroundDropdownOptions(backgroundTextureNames());

    interface->setBlockDropdownOptions(blockTextureNames());
    selectedBlockTexture(0);
}

EditorWindow::~EditorWindow() {
    delete ui;
}

void EditorWindow::wheelEvent(QWheelEvent *event) {
    if (event->angleDelta().y() > 0) {
        if (selectedBlockIndex > 0)
            selectedBlockTexture(selectedBlockIndex - 1);
    } else {
        if (selectedBlockIndex < blocks.size() - 1)
            selectedBlockTexture(selectedBlockIndex + 1);
    }
}

void EditorWindow::selectedBackgroundTexture(size_t index) {
    selectedBackgroundIndex = index;

    QPixmap texture;
    texture.load(QString::fromStdString(backgrounds[selectedBackgroundIndex].source));
    playground->setBackground(texture);
}

void EditorWindow::selectedBlockTexture(size_t index) {
    selectedBlockIndex = index;

    interface->blockDropdownIndexChanged(selectedBlockIndex);
    QPixmap pixelMap;
    pixelMap.load(QString::fromStdString(blocks[selectedBlockIndex].source));
    QBrush texture(pixelMap);
    interface->displayOnPreview(texture);
}

void EditorWindow::exportToFileSystem() {
    std::cout << __func__ << std::endl;
}

std::vector<std::string> EditorWindow::blockTextureNames() {
    std::vector<std::string> blockTextureNames;
    for (const auto& block : blocks) {
        blockTextureNames.push_back(block.name);
    }
    return blockTextureNames;
}

std::vector<std::string> EditorWindow::backgroundTextureNames() {
    std::vector<std::string> backgroundTextureNames;
    for (const auto& background : backgrounds) {
        backgroundTextureNames.push_back(background.name);
    }
    return backgroundTextureNames;
}
