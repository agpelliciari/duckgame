#include "loader.h"

Loader::Loader(const std::string& root): noTexture(loadNoTexture(root)), noTileSet(*this)  {
    loadBackgrounds(root);
    loadBlocks(root);
    loadBoxes(root);
    loadSpawnPlayers(root);
    loadSpawnWeapons(root);
    loadDecorations(root);
    loadTileSetMap(root);
}

std::vector<std::string> Loader::backgroundNames() {
    return names(backgrounds);
}

std::vector<std::string> Loader::blockNames() {
    std::vector<std::string> names;
    for (const TileSet& tileSet : blocks)
        names.push_back(tileSet.name());
    return names;
}

std::vector<std::string> Loader::boxesNames() {
    return names(boxes);
}

std::vector<std::string> Loader::spawnPlayersNames() {
    return names(spawnPlayers);
}

std::vector<std::string> Loader::spawnWeaponsNames() {
    return names(spawnWeapons);
}

std::vector<std::string> Loader::decorationNames() {
    return names(decorations);
}

Texture Loader::backgroundAt(size_t index) {
    return backgrounds.at(index);
}

TileSet Loader::blockAt(size_t index) {
    return blocks.at(index);
}

Texture Loader::boxAt(size_t index) {
    return boxes.at(index);
}

Texture Loader::spawnPlayerAt(size_t index) {
    return spawnPlayers.at(index);
}

Texture Loader::spawnWeaponAt(size_t index) {
    return spawnWeapons.at(index);
}

Texture Loader::decorationAt(size_t index) {
    return decorations.at(index);
}

Texture Loader::background(const std::string& source) {
    return texture(source, backgrounds);
}

TileSet Loader::block(const std::string& source) {
    std::vector<TileSet>::const_iterator iterator = std::find_if(blocks.begin(), blocks.end(),
        [&source](const TileSet& tileSet) {
            return source.find(tileSet.name()) != std::string::npos;
        });

    if (iterator != blocks.end()) {
        return *iterator;
    } else {
        return noTileSet;
    }
}

Texture Loader::box(const std::string& source) {
    return texture(source, boxes);
}

Texture Loader::spawnPlayer(const std::string& source) {
    return texture(source, spawnPlayers);
}

Texture Loader::spawnWeapon(const std::string& source) {
    return texture(source, spawnWeapons);
}

Texture Loader::decoration(const std::string& source) {
    return texture(source, decorations);
}

size_t Loader::backgroundsSize() {
    return backgrounds.size();
}

size_t Loader::blocksSize() {
    return blocks.size();
}

size_t Loader::boxesSize() {
    return boxes.size();
}

size_t Loader::spawnPlayersSize() {
    return spawnPlayers.size();
}

size_t Loader::spawnWeaponsSize() {
    return spawnWeapons.size();
}

size_t Loader::decorationsSize() {
    return decorations.size();
}

std::string Loader::textureNameFor(const std::string& stringRepresentationOfAdyacentsBlocks) {
    try {
        return tileSetMap.at(stringRepresentationOfAdyacentsBlocks);
    } catch (const std::exception& e) {
        throw std::runtime_error("Invalid string representation of adyacents blocks");
    }
}

Loader::~Loader() {}

Texture Loader::loadNoTexture(const std::string& root) {
    QString filePath = QString::fromStdString(root + NO_TEXTURE);
    QPixmap pixelMap;
    if (!pixelMap.load(filePath))
        throw std::runtime_error("There is no notexture file");

    Texture texture;
    texture.name = "notexture";
    texture.source = filePath.toStdString().substr(root.length());
    texture.mapObjectType = MapObjectType::Empty;
    texture.pixelMap = pixelMap;

    return texture;
}

void Loader::loadBackgrounds(const std::string& root) {
    load(root, "/backgrounds", MapObjectType::Background, backgrounds);
}

void Loader::loadBlocks(const std::string& root) {
    QString fullPath = QString::fromStdString(root + "/blocks");
    QDir blocksDirectory(fullPath);

    for (const QFileInfo &fileInfo : blocksDirectory.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot)) {
        if (fileInfo.isDir()) {
            QDir tileSetDirectory(fileInfo.filePath());
            TileSet tileSet(*this, tileSetDirectory);
            blocks.push_back(tileSet);
        }
    }
}

void Loader::loadBoxes(const std::string& root) {
    load(root, "/boxes", MapObjectType::Box, boxes);
}

void Loader::loadSpawnPlayers(const std::string& root) {
    load(root, "/spawns/players", MapObjectType::SpawnPlayer, spawnPlayers);
}

void Loader::loadSpawnWeapons(const std::string& root) {
    load(root, "/spawns/weapons", MapObjectType::SpawnWeapon, spawnWeapons);
}

void Loader::loadDecorations(const std::string& root) {
    load(root, "/decorations", MapObjectType::Decoration, decorations);
}

void Loader::loadTileSetMap(const std::string& root) {
    std::ifstream tileSetMapFile(root + "/blocks/tileSetMap.txt");

    if (tileSetMapFile.is_open()) {
        std::string line;
        while (std::getline(tileSetMapFile, line)) {
            size_t delimiterPos = line.find('-');
            if (delimiterPos != std::string::npos) {
                std::string key = line.substr(0, delimiterPos);
                std::string value = line.substr(delimiterPos + 1);
                tileSetMap[key] = value;
            }
        }
        tileSetMapFile.close();
    } else {
        throw std::runtime_error("There is no tileSetMap file");
    }
}

void Loader::load(const std::string& root, const std::string& path, MapObjectType mapObjectType, std::vector<Texture>& textures) {
    QString fullPath = QString::fromStdString(root + path);
    QDir directory(fullPath);

    QStringList filters;
    filters << "*.png";
    directory.setNameFilters(filters);

    QFileInfoList fileList = directory.entryInfoList(QDir::Files);

    for (const QFileInfo& fileInfo : fileList) {
        QPixmap pixelMap;
        if (!pixelMap.load(fileInfo.filePath()))
            continue;

        Texture texture;
        texture.name = fileInfo.baseName().toStdString();
        texture.source = fileInfo.filePath().toStdString().substr(root.length());
        texture.mapObjectType = mapObjectType;
        texture.pixelMap = pixelMap;

        textures.push_back(texture);

        std::sort(textures.begin(), textures.end(), [](const Texture& a, const Texture& b) {
            auto getNumber = [](const std::string& name) {
                std::string numberPart;
                bool foundDigits = false;
                for (char c : name) {
                    if (std::isdigit(c)) {
                        numberPart += c;
                        foundDigits = true;
                    } else if (foundDigits) {
                        break;
                    }
                }
                try {
                    return numberPart.empty() ? 0 : std::stoi(numberPart);
                } catch (const std::exception&) {
                    return 0;
                }
            };

            return getNumber(a.name) < getNumber(b.name);
        });
    }
}

std::vector<std::string> Loader::names(const std::vector<Texture>& textures) {
    std::vector<std::string> names;
    for (const Texture& texture : textures)
        names.push_back(texture.name);
    return names;
}

Texture Loader::texture(const std::string& source, const std::vector<Texture>& textures) {
    std::vector<Texture>::const_iterator iterator = std::find_if(textures.begin(), textures.end(),
        [&source](const Texture& tileSet) {
            return tileSet.source == source;
        });

    if (iterator != textures.end()) {
        return *iterator;
    } else {
        return noTexture;
    }
}

Texture Loader::getNoTexture() {
    return noTexture;
}