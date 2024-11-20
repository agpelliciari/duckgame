#include "./map_loader.h"

#include <iostream>
#include <filesystem>
static const char* DIR_MAPS = "res/maps/";
static const char* EXT = ".yaml";


MapLoader::MapLoader(const char * root_maps) {
     for (const auto& entry: std::filesystem::directory_iterator(root_maps)){
           if(entry.is_regular_file()){
               auto path = entry.path();
               
               if(path.extension() == EXT){
                    list_maps.push_back(path.filename().replace_extension().string());
               }
           }
     }
     
     for(const std::string& map: list_maps){
         std::cout << "REGISTERED MAP: " << map<<std::endl;
     }
}

const std::vector<std::string>& MapLoader::registeredMaps() const{
      return list_maps;
}


MapLoader::MapLoader() : MapLoader(DIR_MAPS){

}

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
