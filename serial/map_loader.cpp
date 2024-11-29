#include "./map_loader.h"

#include <iostream>
#include <filesystem>

static const char* DIR_MAPS = "res/maps/";
static const char* EXT = ".yaml";


MapLoader::MapLoader(const char * root_maps): root(root_maps), dev(), map_gen(dev()){
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
     
     distribute = std::uniform_int_distribution<std::mt19937::result_type>(0, list_maps.size()-1);
}

const std::vector<std::string>& MapLoader::registeredMaps() const{
      return list_maps;
}


MapLoader::MapLoader() : MapLoader(DIR_MAPS){

}

MapDeserializer& MapLoader::getRandomMap(){
       int ind = distribute(map_gen);     
       std::cout<< "Should select random map! DID ?"<< ind<< "\n";
       
       return getLoader(list_maps[ind].c_str());
}

MapDeserializer& MapLoader::getLoader(const char* mapname) {

    std::string name(root);
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
