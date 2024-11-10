#include "loader.h"

Loader::Loader(const std::string& root) {
    loadBackgrounds(root);
    loadBlocks(root);
    loadBoxes(root);
}

std::vector<std::string> Loader::backgroundNames() {
    return names(backgrounds);
}

std::vector<std::string> Loader::blockNames() {
    return names(blocks);
}

std::vector<std::string> Loader::boxesNames() {
    return names(boxes);
}

Texture Loader::backgroundAt(size_t index) {
    return backgrounds.at(index);
}

Texture Loader::blockAt(size_t index) {
    return blocks.at(index);
}

Texture Loader::boxAt(size_t index) {
    return boxes.at(index);
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

Loader::~Loader() {}

void Loader::loadBackgrounds(const std::string& root) {
    load(root, "/backgrounds", TextureType::TBackground, backgrounds);
}

void Loader::loadBlocks(const std::string& root) {
    load(root, "/blocks", TextureType::TBlock, blocks);
}

void Loader::loadBoxes(const std::string& root) {
    load(root, "/boxes", TextureType::TBlock, boxes);
}

void Loader::load(const std::string& root, const std::string& path, TextureType type, std::vector<Texture>& textures) {
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
        texture.source = fileInfo.filePath().toStdString();
        texture.textureType = type;
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