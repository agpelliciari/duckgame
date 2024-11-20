#ifndef LIB_MAP_LOADER
#define LIB_MAP_LOADER

#include <list>
#include <vector>
#include <string>
#include "./map_deserializer.h"


class MapLoader {
protected:
    struct ReferencedMap {
        MapDeserializer deserial;
        int count;
        explicit ReferencedMap(const std::string& name): deserial(name), count(1) {}
    };
    
    std::string root;
    std::list<struct ReferencedMap> maps;  // cppcheck-suppress unusedStructMember
    std::vector<std::string> list_maps;
public:
    MapLoader(const char* root_maps);
    MapLoader();
    // Asumamos por ahora que no se quiere permitir copias..
    MapLoader(const MapLoader&) = delete;
    MapLoader& operator=(const MapLoader&) = delete;

    // Permitamos el mov... por mas que no sea realmente eficiente.
    MapLoader(MapLoader&&) = delete;
    MapLoader& operator=(MapLoader&&) = delete;

    MapDeserializer& getLoader(const char* mapname);

    void removeLoader(const std::string& loader_id);

    const std::vector<std::string>& registeredMaps() const;

};
#endif
