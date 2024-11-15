#include "./map_loader.h"

#include <iostream>
static const char* DIR_MAPS = "res/maps/";
static const char* EXT = ".yaml";


MapLoader::MapLoader() {}

MapDeserializer& MapLoader::getLoader(const char* mapname) {

    std::string name(DIR_MAPS);
    name.append(mapname);
    name.append(EXT);

    for (ReferencedMap& ref: maps) {
        // cppcheck-suppress useStlAlgorithm
        if (ref.deserial.getMapName() == name) {
            ref.count++;
            return ref.deserial;
        }
    }

    std::cout << "LOADING NEW MAP " << name << std::endl;

    // Por ahora pone uno default ... por tema espacios?
    //name = std::string(DIR_MAPS);
    //name.append("map3");
    //name.append(EXT);


    // No estaba.

    ReferencedMap& ref = maps.emplace_back(name);
    return ref.deserial;
}

void MapLoader::removeLoader(const std::string& loader_id) {
    for (auto refit = maps.begin(); refit != maps.end();) {
        if (refit->deserial.getMapName() != loader_id) {
            ++refit;
            continue;
        }

        refit->count--;
        if (refit->count <= 0) {
            std::cout << "ERASING MAP " << refit->deserial.getMapName() << std::endl;
            maps.erase(refit);
        }
        return;
    }
}
