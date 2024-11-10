#ifndef LOADER_H
#define LOADER_H

#include <QDir>
#include <QFileInfoList>
#include <QPixmap>

#include <string>
#include <vector>

enum TextureType {
    TBackground,
    TBlock,
    TSpawn,
    TTBox,
    TDecoration
};

struct Texture {
    std::string name;
    std::string source;
    TextureType textureType;
    QPixmap pixelMap;
};

class Loader {
private:
    std::vector<Texture> backgrounds;
    std::vector<Texture> blocks;
    std::vector<Texture> boxes;

public:
    explicit Loader(const std::string& root);

    std::vector<std::string> backgroundNames();
    std::vector<std::string> blockNames();
    std::vector<std::string> boxesNames();

    Texture backgroundAt(size_t index);
    Texture blockAt(size_t index);
    Texture boxAt(size_t index);

    size_t backgroundsSize();
    size_t blocksSize();
    size_t boxesSize();

    ~Loader();

private:
    void loadBackgrounds(const std::string& root);

    void loadBlocks(const std::string& root);

    void loadBoxes(const std::string& root);

    void load(const std::string& root, const std::string& path, TextureType type, std::vector<Texture>& textures);

    std::vector<std::string> names(const std::vector<Texture>& textures);
};

#endif
