#ifndef TILESET_H
#define TILESET_H

#include <QDir>

#include <vector>
#include <string>
#include <map>

#include "types.h"

class Loader;

class TileSet {
private:
    Loader& loader;
    std::string _name;
    std::map<std::string, Texture> textures;

public:
    explicit TileSet(Loader& loader, QDir directory);

    std::string name() const;

    Texture preview();

    Texture textureFor(const std::string& stringRepresentationOfAdyacentsBlocks);

    ~TileSet();
};

#endif
