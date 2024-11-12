#include "tileset.h"
#include "loader.h"

TileSet::TileSet(Loader& loader, QDir directory): loader(loader), _name(directory.dirName().toStdString()) {
    QFileInfoList fileList = directory.entryInfoList(QDir::Files);

    for (const QFileInfo& fileInfo : fileList) {
        QPixmap pixelMap;
        if (!pixelMap.load(fileInfo.filePath()))
            continue;

        Texture texture;
        texture.name = fileInfo.baseName().toStdString();
        texture.source = fileInfo.filePath().toStdString();
        texture.mapObjectType = MapObjectType::Block;
        texture.pixelMap = pixelMap;

        textures.emplace(texture.name, texture);
    }
}

std::string TileSet::name() const {
    return _name;
}

Texture TileSet::preview() {
    try {
        return textures.at("37");
    } catch (const std::exception& e) {
        throw std::runtime_error("Missing preview block texture");
    }
}

Texture TileSet::textureFor(const std::string& stringRepresentationOfAdyacentsBlocks) {
    try {
        return textures.at(loader.textureNameFor(stringRepresentationOfAdyacentsBlocks));
    } catch (const std::exception& e) {
        throw std::runtime_error("Missing block texture");
    }
}

TileSet::~TileSet() {}