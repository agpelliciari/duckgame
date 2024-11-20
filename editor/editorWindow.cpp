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
                case MapObjectType::SpawnPlayer:
                    selectSpawnPlayerTexture(index);
                    break;
                case MapObjectType::SpawnWeapon:
                    selectSpawnWeaponTexture(index);
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
        .onExport = [this]() { exportToFileSystem(); },
        .onImport = [this]() { importFromFileSystem(); }
    }, this)),
    playground(new Playground(PlaygroundHandler{
        .onLeftClick = [this](QPoint position) {
            switch (editorIsCurrentlySetting) {
                case MapObjectType::Background:
                    break;
                case MapObjectType::Block:
                    playground->addBlock(position, loader.blockAt(selectedBlockIndex));
                    break;
                case MapObjectType::SpawnPlayer:
                    playground->addSpawnPlayer(position, loader.spawnPlayerAt(selectedSpawnPlayerIndex));
                    break;
                case MapObjectType::SpawnWeapon:
                    playground->addSpawnWeapon(position, loader.spawnWeaponAt(selectedSpawnWeaponIndex));
                    break;
                case MapObjectType::Box:
                    playground->addBox(position, loader.boxAt(selectedBoxIndex));
                    break;
                case MapObjectType::Decoration:
                    playground->addDecoration(position, loader.decorationAt(selectedDecorationIndex));
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
                    playground->removeBlock(position, loader.blockAt(selectedBlockIndex));
                    break;
                case MapObjectType::SpawnPlayer:
                    playground->removeSpawnPlayer(position);
                    break;
                case MapObjectType::SpawnWeapon:
                    playground->removeSpawnWeapon(position);
                    break;
                case MapObjectType::Box:
                    playground->removeBox(position);
                    break;
                case MapObjectType::Decoration:
                    playground->removeDecoration(position);
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
        "Player Spawns",
        "Weapon Spawns",
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
                case MapObjectType::SpawnPlayer:
                    if (selectedSpawnPlayerIndex > 0)
                        selectSpawnPlayerTexture(selectedSpawnPlayerIndex - 1);
                    break;
                case MapObjectType::SpawnWeapon:
                    if (selectedSpawnWeaponIndex > 0)
                        selectSpawnWeaponTexture(selectedSpawnWeaponIndex - 1);
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
                case MapObjectType::SpawnPlayer:
                    if (selectedSpawnPlayerIndex < loader.spawnPlayersSize() - 1)
                        selectSpawnPlayerTexture(selectedSpawnPlayerIndex + 1);
                    break;
                case MapObjectType::SpawnWeapon:
                    if (selectedSpawnWeaponIndex < loader.spawnWeaponsSize() - 1)
                        selectSpawnWeaponTexture(selectedSpawnWeaponIndex + 1);
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
            interface->displayMapObjectOnPreview(loader.blockAt(selectedBlockIndex).preview());
            break;
        case MapObjectType::SpawnPlayer:
            interface->setSelectorDropdownOptions(loader.spawnPlayersNames());
            interface->selectorDropdownIndexChanged(selectedSpawnPlayerIndex);
            interface->displayMapObjectOnPreview(loader.spawnPlayerAt(selectedSpawnPlayerIndex));
            break;
        case MapObjectType::SpawnWeapon:
            interface->setSelectorDropdownOptions(loader.spawnWeaponsNames());
            interface->selectorDropdownIndexChanged(selectedSpawnWeaponIndex);
            interface->displayMapObjectOnPreview(loader.spawnWeaponAt(selectedSpawnWeaponIndex));
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
    interface->displayMapObjectOnPreview(loader.blockAt(selectedBlockIndex).preview());
}

void EditorWindow::selectSpawnPlayerTexture(size_t index) {
    selectedSpawnPlayerIndex = index;
    interface->selectorDropdownIndexChanged(selectedSpawnPlayerIndex);
    interface->displayMapObjectOnPreview(loader.spawnPlayerAt(selectedSpawnPlayerIndex));
}

void EditorWindow::selectSpawnWeaponTexture(size_t index) {
    selectedSpawnWeaponIndex = index;
    interface->selectorDropdownIndexChanged(selectedSpawnWeaponIndex);
    interface->displayMapObjectOnPreview(loader.spawnWeaponAt(selectedSpawnWeaponIndex));
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
    QString filePath = QFileDialog::getSaveFileName(this, EditorWindow::EXPORT, QString(DATA_PATH) + EditorWindow::MAPS_SOURCE, EditorWindow::FILE_FILTERS);

    if (filePath.isEmpty() || filePath.isNull())
        return;

    try {
        const int maxWidth = playground->maxWidthToExport();
        const int maxHeight = playground->maxHeightToExport();
        const MapObjectData background = playground->backgroundToExport();
        const std::vector<MapObjectData> blocks = playground->blocksToExport();
        const std::vector<MapObjectData> spawnPlayers = playground->spawnPlayersToExport();
        const std::vector<MapObjectData> spawnWeapons = playground->spawnWeaponsToExport();
        const std::vector<MapObjectData> boxes = playground->boxesToExport();
        const std::vector<MapObjectData> decorations = playground->decorationsToExport();

        MapSerializer serial(maxWidth, maxHeight);
        serial.setBackground(background.texture.substr(5));

        for (const auto& block : blocks) {
            serial.addBlock(block.column, block.row, block.zIndex, block.texture.substr(5));
        }

        for (const auto& spawnPlayer : spawnPlayers) {
            serial.addPlayerSpawn(spawnPlayer.column, spawnPlayer.row, spawnPlayer.zIndex, spawnPlayer.texture.substr(5));
        }

        for (const auto& spawnWeapon : spawnWeapons) {
            serial.addItemSpawn(spawnWeapon.column, spawnWeapon.row, spawnWeapon.zIndex, spawnWeapon.texture.substr(5));
        }

        for (const auto& box : boxes) {
            serial.addBox(box.column, box.row, box.zIndex, box.texture.substr(5));
        }

        for (const auto& decoration : decorations) {
            serial.addDecoration(decoration.column , decoration.row, decoration.zIndex, decoration.texture.substr(5));
        }

        serial.save(filePath.toStdString());
        interface->displayNotificationSuccess("The map was exported successfully");
    } catch (const std::exception& err) {
        interface->displayNotificationError(std::string("Error: ") + err.what());
    }
}

void EditorWindow::importFromFileSystem() {
    try {
        QString filePath = QFileDialog::getOpenFileName(this, EditorWindow::IMPORT, QString(DATA_PATH) + EditorWindow::MAPS_SOURCE, EditorWindow::FILE_FILTERS);

        if (filePath.isEmpty() || filePath.isNull())
            return;

        /*MapImporter deserial(filePath.toStdString());

        int width = deserial.getWidth();
        int height = deserial.getHeight();

        const std::string background = deserial.getBackground();

        const std::vector<MapObjectDataToImport> blocks = deserial.getBlocks();
        const std::vector<MapObjectDataToImport> spawnPlayers = deserial.getPlayerSpawns();
        const std::vector<MapObjectDataToImport> spawnWeapons = deserial.getItemSpawns();
        const std::vector<MapObjectDataToImport> boxes = deserial.getBoxes();
        const std::vector<MapObjectDataToImport> decorations = deserial.getDecorations();*/
        
        interface->displayNotificationSuccess("The map was imported successfully");
    } catch (const std::exception& err) {
        interface->displayNotificationError(std::string("Error: ") + err.what());
    }
}
