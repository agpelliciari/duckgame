#include "editorWindow.h"
#include "./ui_editorWindow.h"

#include <iostream>

EditorWindow::EditorWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::EditorWindow),
    loader("./res"),
    interface(new Interface(InterfaceHandler{
        .onEditorModeDropdownChanged = [this](MapObjectType mode) {
            selectEditorMode(mode);
        },
        .onSelectorDropdownIndexChanged = [this](size_t index) {
            switch (editorIsCurrentlySetting) {
                case MapObjectType::Background:
                    selectBackgroundTexture(index);
                    break;
                case MapObjectType::Block:
                    selectBlockTexture(index);
                    break;
                case MapObjectType::Spawn:
                    selectSpawnTexture(index);
                    break;
                case MapObjectType::Box:
                    selectBoxTexture(index);
                    break;
                case MapObjectType::Decoration:
                    selectDecorationTexture(index);
                    break;
                default:
                    break;
            }
        },
        .onExport = [this]() { exportToFileSystem(); }
    }, this)),
    playground(new Playground(PlaygroundHandler{
        .onLeftClick = [this](QPoint position) {
            switch (editorIsCurrentlySetting) {
                case MapObjectType::Background:
                    break;
                case MapObjectType::Block:
                    playground->addPhysicalObject(position, loader.blockAt(selectedBlockIndex));
                    break;
                case MapObjectType::Spawn:
                    playground->addNonPhysicalObject(position, loader.spawnAt(selectedSpawnIndex));
                    break;
                case MapObjectType::Box:
                    playground->addPhysicalObject(position, loader.boxAt(selectedBoxIndex));
                    break;
                case MapObjectType::Decoration:
                    playground->addNonPhysicalObject(position, loader.decorationAt(selectedDecorationIndex));
                    break;
                default:
                    break;
            }
        },
        .onRightClick = [this](QPoint position) {
            switch (editorIsCurrentlySetting) {
                case MapObjectType::Background:
                    break;
                case MapObjectType::Block:
                    playground->removePhysicalObject(position);
                    break;
                case MapObjectType::Spawn:
                    playground->removeNonPhysicalObject(position);
                    break;
                case MapObjectType::Box:
                    playground->removePhysicalObject(position);
                    break;
                case MapObjectType::Decoration:
                    playground->removeNonPhysicalObject(position);
                    break;
                default:
                    break;
            }
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
        "Spawns",
        "Boxes",
        "Decorations"
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
            switch (editorIsCurrentlySetting) {
                case MapObjectType::Background:
                    if (selectedBackgroundIndex > 0)
                        selectBackgroundTexture(selectedBackgroundIndex - 1);
                    break;
                case MapObjectType::Block:
                    if (selectedBlockIndex > 0)
                        selectBlockTexture(selectedBlockIndex - 1);
                    break;
                case MapObjectType::Spawn:
                    if (selectedSpawnIndex > 0)
                        selectSpawnTexture(selectedSpawnIndex - 1);
                    break;
                case MapObjectType::Box:
                    if (selectedBoxIndex > 0)
                        selectBoxTexture(selectedBoxIndex - 1);
                    break;
                case MapObjectType::Decoration:
                    if (selectedDecorationIndex > 0)
                        selectDecorationTexture(selectedDecorationIndex - 1);
                    break;
                default:
                    break;
            }
        } else {
            switch (editorIsCurrentlySetting) {
                case MapObjectType::Background:
                    if (selectedBackgroundIndex < loader.backgroundsSize() - 1)
                        selectBackgroundTexture(selectedBackgroundIndex + 1);
                    break;
                case MapObjectType::Block:
                    if (selectedBlockIndex < loader.blocksSize() - 1)
                        selectBlockTexture(selectedBlockIndex + 1);
                    break;
                case MapObjectType::Spawn:
                    if (selectedSpawnIndex < loader.spawnsSize() - 1)
                        selectSpawnTexture(selectedSpawnIndex + 1);
                    break;
                case MapObjectType::Box:
                    if (selectedBoxIndex < loader.boxesSize() - 1)
                        selectBoxTexture(selectedBoxIndex + 1);
                    break;
                case MapObjectType::Decoration:
                    if (selectedDecorationIndex < loader.decorationsSize() - 1)
                        selectDecorationTexture(selectedDecorationIndex + 1);
                    break;
                default:
                    break;
            }
        }
    }
}

void EditorWindow::selectEditorMode(MapObjectType mode) {
    editorIsCurrentlySetting = mode;
    switch (editorIsCurrentlySetting) {
        case MapObjectType::Background:
            interface->setSelectorDropdownOptions(loader.backgroundNames());
            interface->selectorDropdownIndexChanged(selectedBackgroundIndex);
            interface->displayNoneOnPreview();
            break;
        case MapObjectType::Block:
            interface->setSelectorDropdownOptions(loader.blockNames());
            interface->selectorDropdownIndexChanged(selectedBlockIndex);
            interface->displayMapObjectOnPreview(loader.blockAt(selectedBlockIndex));
            break;
        case MapObjectType::Spawn:
            interface->setSelectorDropdownOptions(loader.spawnNames());
            interface->selectorDropdownIndexChanged(selectedSpawnIndex);
            interface->displayMapObjectOnPreview(loader.spawnAt(selectedSpawnIndex));
            break;
        case MapObjectType::Box:
            interface->setSelectorDropdownOptions(loader.boxesNames());
            interface->selectorDropdownIndexChanged(selectedBoxIndex);
            interface->displayMapObjectOnPreview(loader.boxAt(selectedBoxIndex));
            break;
        case MapObjectType::Decoration:
            interface->setSelectorDropdownOptions(loader.decorationNames());
            interface->selectorDropdownIndexChanged(selectedDecorationIndex);
            interface->displayMapObjectOnPreview(loader.decorationAt(selectedDecorationIndex));
            break;
        default:
            break;
    }
}

void EditorWindow::selectBackgroundTexture(size_t index) {
    selectedBackgroundIndex = index;
    interface->selectorDropdownIndexChanged(selectedBackgroundIndex);
    playground->setBackground(loader.backgroundAt(selectedBackgroundIndex));
}

void EditorWindow::selectBlockTexture(size_t index) {
    selectedBlockIndex = index;
    interface->selectorDropdownIndexChanged(selectedBlockIndex);
    interface->displayMapObjectOnPreview(loader.blockAt(selectedBlockIndex));
}

void EditorWindow::selectSpawnTexture(size_t index) {
    selectedSpawnIndex = index;
    interface->selectorDropdownIndexChanged(selectedSpawnIndex);
    interface->displayMapObjectOnPreview(loader.spawnAt(selectedSpawnIndex));
}

void EditorWindow::selectBoxTexture(size_t index) {
    selectedBoxIndex = index;
    interface->selectorDropdownIndexChanged(selectedBoxIndex);
    interface->displayMapObjectOnPreview(loader.boxAt(selectedBoxIndex));
}

void EditorWindow::selectDecorationTexture(size_t index) {
    selectedDecorationIndex = index;
    interface->selectorDropdownIndexChanged(selectedDecorationIndex);
    interface->displayMapObjectOnPreview(loader.decorationAt(selectedDecorationIndex));
}

void EditorWindow::exportToFileSystem() {
    const MapObjectData background = playground->backgroundToExport();
    const std::vector<MapObjectData> blocks = playground->blocksToExport();
    const std::vector<MapObjectData> spawns = playground->spawnsToExport();
    const std::vector<MapObjectData> boxes = playground->boxesToExport();
    const std::vector<MapObjectData> decorations = playground->decorationsToExport();

    std::cout << "Background:\n";
    std::cout << "Row: " << background.row 
                  << ", Column: " << background.column 
                  << ", Type: " << background.mapObjectType 
                  << ", Texture: " << background.texture << "\n";

    std::cout << "Blocks:\n";
    for (const auto& block : blocks) {
        std::cout << "Row: " << block.row 
                  << ", Column: " << block.column 
                  << ", Type: " << block.mapObjectType 
                  << ", Texture: " << block.texture << "\n";
    }

    std::cout << "Spawns:\n";
    for (const auto& spawn : spawns) {
        std::cout << "Row: " << spawn.row 
                  << ", Column: " << spawn.column 
                  << ", Type: " << spawn.mapObjectType 
                  << ", Texture: " << spawn.texture << "\n";
    }

    std::cout << "Boxes:\n";
    for (const auto& box : boxes) {
        std::cout << "Row: " << box.row 
                  << ", Column: " << box.column 
                  << ", Type: " << box.mapObjectType 
                  << ", Texture: " << box.texture << "\n";
    }

    std::cout << "Decorations:\n";
    for (const auto& decoration : decorations) {
        std::cout << "Row: " << decoration.row 
                  << ", Column: " << decoration.column 
                  << ", Type: " << decoration.mapObjectType 
                  << ", Texture: " << decoration.texture << "\n";
    }
}
