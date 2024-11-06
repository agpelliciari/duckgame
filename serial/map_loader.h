#ifndef LIB_MAP_LOADER
#define LIB_MAP_LOADER

#include <string>
#include <vector>

#include "./map_deserializer.h"


class MapLoader {
protected:
    struct ReferencedMap {
        MapInfo info;
        int count;
        ReferencedMap(const std::string& name, const struct MapPoint _size, uint8_t _bk):
                info(name, _size, _bk), count(1) {}
    };

    std::vector<struct ReferencedMap> maps;  // cppcheck-suppress unusedStructMember

public:
    MapLoader();
    // Asumamos por ahora que no se quiere permitir copias..
    MapLoader(const MapLoader&) = delete;
    MapLoader& operator=(const MapLoader&) = delete;

    // Permitamos el mov... por mas que no sea realmente eficiente.
    MapLoader(MapLoader&&) = delete;
    MapLoader& operator=(MapLoader&&) = delete;

    MapInfo& loadMap(const char* mapname);
    void removeMap(const std::string& name);
};
#endif
