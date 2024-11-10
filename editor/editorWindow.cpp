#include "editorWindow.h"
#include "./ui_editorWindow.h"

#include <iostream>

EditorWindow::EditorWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::EditorWindow),
    loader("./res"),
    interface(new Interface(InterfaceHandler{
        .onEditorModeDropdownChanged = [this](EditorMode mode) {
            selectEditorMode(mode);
        },
        .onSelectorDropdownIndexChanged = [this](size_t index) {
            switch (editorMode) {
                case EditorMode::EMBackground:
                    selectBackgroundTexture(index);
                    break;
                case EditorMode::EMBlock:
                    selectBlockTexture(index);
                    break;
                case EditorMode::EMBox:
                    selectBoxTexture(index);
                    break;
                case EditorMode::EMSpawn:
                    selectSpawnTexture(index);
                    break;
                default:
                    break;
            }
        },
        .onExport = [this]() { exportToFileSystem(); }
    }, this)),
    playground(new Playground(PlaygroundHandler{
        .onLeftClick = [this](QPoint position) {
            switch (editorMode) {
                case EditorMode::EMBackground:
                    break;
                case EditorMode::EMBlock:
                    playground->addBlock(position, loader.blockAt(selectedBlockIndex).pixelMap);
                    break;
                case EditorMode::EMBox:
                    playground->addBlock(position, loader.boxAt(selectedBoxIndex).pixelMap);
                    break;
                case EditorMode::EMSpawn:
                    playground->addBlock(position, loader.spawnAt(selectedSpawnIndex).pixelMap);
                    break;
                default:
                    break;
            }
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

    interface->setEditorModeDropdownOptions({
        "Backgrounds",
        "Blocks",
        "Boxes",
        "Spawns"
    });
}

EditorWindow::~EditorWindow() {
    delete ui;
}

void EditorWindow::wheelEvent(QWheelEvent *event) {
    if (event->modifiers() & Qt::ControlModifier) {
        if (event->angleDelta().y() > 0) {
            playground->zoomIn();
        } else {
            playground->zoomOut();
        }
    } else {
        if (event->angleDelta().y() > 0) {
            switch (editorMode) {
                case EditorMode::EMBackground:
                    if (selectedBackgroundIndex > 0)
                        selectBackgroundTexture(selectedBackgroundIndex - 1);
                    break;
                case EditorMode::EMBlock:
                    if (selectedBlockIndex > 0)
                        selectBlockTexture(selectedBlockIndex - 1);
                    break;
                case EditorMode::EMBox:
                    if (selectedBoxIndex > 0)
                        selectBoxTexture(selectedBoxIndex - 1);
                    break;
                case EditorMode::EMSpawn:
                    if (selectedSpawnIndex > 0)
                        selectSpawnTexture(selectedSpawnIndex - 1);
                    break;
                default:
                    break;
            }
        } else {
            switch (editorMode) {
                case EditorMode::EMBackground:
                    if (selectedBackgroundIndex < loader.backgroundsSize() - 1)
                        selectBackgroundTexture(selectedBackgroundIndex + 1);
                    break;
                case EditorMode::EMBlock:
                    if (selectedBlockIndex < loader.blocksSize() - 1)
                        selectBlockTexture(selectedBlockIndex + 1);
                    break;
                case EditorMode::EMBox:
                    if (selectedBoxIndex < loader.boxesSize() - 1)
                        selectBoxTexture(selectedBoxIndex + 1);
                    break;
                case EditorMode::EMSpawn:
                    if (selectedSpawnIndex < loader.spawnsSize() - 1)
                        selectSpawnTexture(selectedSpawnIndex + 1);
                    break;
                default:
                    break;
            }
        }
    }
}

void EditorWindow::selectEditorMode(EditorMode mode) {
    editorMode = mode;
    switch (editorMode) {
        case EditorMode::EMBackground:
            interface->setSelectorDropdownOptions(loader.backgroundNames());
            interface->selectorDropdownIndexChanged(selectedBackgroundIndex);
            interface->displayNoneOnPreview();
            break;
        case EditorMode::EMBlock:
            interface->setSelectorDropdownOptions(loader.blockNames());
            interface->selectorDropdownIndexChanged(selectedBlockIndex);
            interface->displayBlockOnPreview(loader.blockAt(selectedBlockIndex).pixelMap);
            break;
        case EditorMode::EMBox:
            interface->setSelectorDropdownOptions(loader.boxesNames());
            interface->selectorDropdownIndexChanged(selectedBoxIndex);
            interface->displayBlockOnPreview(loader.boxAt(selectedBoxIndex).pixelMap);
            break;
        case EditorMode::EMSpawn:
            interface->setSelectorDropdownOptions(loader.spawnNames());
            interface->selectorDropdownIndexChanged(selectedSpawnIndex);
            interface->displayBlockOnPreview(loader.spawnAt(selectedSpawnIndex).pixelMap);
            break;
        default:
            break;
    }
}

void EditorWindow::selectBackgroundTexture(size_t index) {
    selectedBackgroundIndex = index;
    interface->selectorDropdownIndexChanged(selectedBackgroundIndex);
    playground->setBackground(loader.backgroundAt(selectedBackgroundIndex).pixelMap);
}

void EditorWindow::selectBlockTexture(size_t index) {
    selectedBlockIndex = index;
    interface->selectorDropdownIndexChanged(selectedBlockIndex);
    interface->displayBlockOnPreview(loader.blockAt(selectedBlockIndex).pixelMap);
}

void EditorWindow::selectBoxTexture(size_t index) {
    selectedBoxIndex = index;
    interface->selectorDropdownIndexChanged(selectedBoxIndex);
    interface->displayBlockOnPreview(loader.boxAt(selectedBoxIndex).pixelMap);
}

void EditorWindow::selectSpawnTexture(size_t index) {
    selectedSpawnIndex = index;
    interface->selectorDropdownIndexChanged(selectedSpawnIndex);
    interface->displayBlockOnPreview(loader.spawnAt(selectedSpawnIndex).pixelMap);
}

void EditorWindow::exportToFileSystem() {
    const std::vector<std::string> blocks = loader.blockNames();

    for (const auto& block : blocks) {
        std::cout << block << std::endl;
    }
}
