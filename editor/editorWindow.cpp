#include "editorWindow.h"
#include "./ui_editorWindow.h"

#include <iostream>

EditorWindow::EditorWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::EditorWindow),
    interface(new Interface(InterfaceHandler{
        .onBlockDropdownIndexChanged = [this](size_t index) {
            selectedTextureIndex = index;
            QPixmap pixelMap;
            pixelMap.load(QString::fromStdString(textures[selectedTextureIndex].source));
            QBrush texture(pixelMap);
            interface->displayOnPreview(texture);
        },
        .onExport = [this]() { exportToFileSystem(); }
    }, this)),
    playground(new Playground(PlaygroundHandler{
        .onLeftClick = [this](QPoint position) {
            QPixmap texturePixmap;
            texturePixmap.load(QString::fromStdString(textures[selectedTextureIndex].source));
            QBrush texture(texturePixmap);
            playground->addBlock(position, texture);
        },
        .onRightClick = [this](QPoint position) {
            playground->removeBlock(position);
        }
    }, this))
{
    ui->setupUi(this);

    textures = {
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

    interface->setMaximumWidth(200);
    ui->horizontalLayout->addWidget(interface);
    ui->horizontalLayout->addWidget(playground, 1);

    interface->setBlockDropdownOptions(blockTextureNames());
    selectedBlockTexture(0);
}

EditorWindow::~EditorWindow() {
    delete ui;
}

void EditorWindow::wheelEvent(QWheelEvent *event) {
    if (event->angleDelta().y() > 0) {
        if (selectedTextureIndex > 0)
            selectedBlockTexture(selectedTextureIndex - 1);
    } else {
        if (selectedTextureIndex < textures.size() - 1)
            selectedBlockTexture(selectedTextureIndex + 1);
    }
}

void EditorWindow::selectedBlockTexture(size_t index) {
    selectedTextureIndex = index;

    interface->blockDropdownIndexChanged(selectedTextureIndex);
    QPixmap pixelMap;
    pixelMap.load(QString::fromStdString(textures[selectedTextureIndex].source));
    QBrush texture(pixelMap);
    interface->displayOnPreview(texture);
}

void EditorWindow::exportToFileSystem() {
    std::cout << __func__ << std::endl;
}

std::vector<std::string> EditorWindow::blockTextureNames() {
    std::vector<std::string> blockTextureNames;
    for (const auto& texture : textures) {
        blockTextureNames.push_back(texture.name);
    }
    return blockTextureNames;
}
