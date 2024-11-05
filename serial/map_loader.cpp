#include "./map_loader.h"

#include <iostream>
static const char* DIR_MAPS = "res/maps/";
static const char* EXT = ".yaml";


MapLoader::MapLoader() {}

MapInfo& MapLoader::loadMap(const char* mapname) {

    std::string name(DIR_MAPS);
    name.append(mapname);
    name.append(EXT);

    for (ReferencedMap& ref: maps) {
        // cppcheck-suppress useStlAlgorithm
        if (ref.info.mapname == name) {
            ref.count++;
            return ref.info;
        }
    }

    std::cout << "LOADING NEW MAP " << name << std::endl;
    // No estaba.
    MapDeserializer deserial(name);

    ReferencedMap& ref = maps.emplace_back(name, deserial.readSize(), deserial.readBackground());

    deserial.readBlocks(ref.info.blocks);
    deserial.readPlayerSpawns(ref.info.spawns_player);
    deserial.readItemSpawns(ref.info.spawns_items);
    deserial.readBoxes(ref.info.boxes);


    return ref.info;
}

void MapLoader::removeMap(const std::string& name) {
    for (auto refit = maps.begin(); refit != maps.end();) {
        if (refit->info.mapname != name) {
            ++refit;
            continue;
        }
        refit->count--;
        if (refit->count <= 0) {
            std::cout << "ERASING MAP " << refit->info.mapname << std::endl;
            maps.erase(refit);
        }
        return;
    }
}
