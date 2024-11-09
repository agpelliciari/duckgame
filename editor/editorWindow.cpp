#include "editorWindow.h"
#include "./ui_editorWindow.h"

#include <iostream>

EditorWindow::EditorWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::EditorWindow),
    loader("./res"),
    interface(new Interface(InterfaceHandler{
        .onBackgroundDropdownIndexChanged = [this](size_t index) {
            selectBackgroundTexture(index);
        },
        .onBlockDropdownIndexChanged = [this](size_t index) {
            selectBlockTexture(index);
        },
        .onExport = [this]() { exportToFileSystem(); }
    }, this)),
    playground(new Playground(PlaygroundHandler{
        .onLeftClick = [this](QPoint position) {
            QBrush texture(loader.blockAt(selectedBlockIndex).pixelMap);
            playground->addBlock(position, texture);
        },
        .onRightClick = [this](QPoint position) {
            playground->removeBlock(position);
        }
    }, this))
{
    ui->setupUi(this);

    interface->setMaximumWidth(200);
    ui->horizontalLayout->addWidget(interface);
    ui->horizontalLayout->addWidget(playground, 1);

    interface->setBackgroundDropdownOptions(loader.backgroundNames());
    interface->setBlockDropdownOptions(loader.blockNames());
    selectBlockTexture(0);
}

EditorWindow::~EditorWindow() {
    delete ui;
}

void EditorWindow::wheelEvent(QWheelEvent *event) {
    if (event->angleDelta().y() > 0) {
        if (selectedBlockIndex > 0)
            selectBlockTexture(selectedBlockIndex - 1);
    } else {
        if (selectedBlockIndex < loader.blocksSize() - 1)
            selectBlockTexture(selectedBlockIndex + 1);
    }
}

void EditorWindow::selectBackgroundTexture(size_t index) {
    selectedBackgroundIndex = index;
    playground->setBackground(loader.backgroundAt(selectedBackgroundIndex).pixelMap);
}

void EditorWindow::selectBlockTexture(size_t index) {
    selectedBlockIndex = index;
    interface->blockDropdownIndexChanged(selectedBlockIndex);
    QBrush texture(loader.blockAt(selectedBlockIndex).pixelMap);
    interface->displayOnPreview(texture);
}

void EditorWindow::exportToFileSystem() {
    const std::vector<std::string> blocks = loader.backgroundNames();

    for (const auto& block : blocks) {
        std::cout << block << std::endl;
    }
}
