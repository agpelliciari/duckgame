#ifndef LIB_MAP_LOADER
#define LIB_MAP_LOADER

#include <string>
#include <vector>

#include "./map_deserializer.h"

struct MapInfo {
    std::string mapname;
    struct MapPoint size;
    uint8_t bk;
    std::vector<struct BlockDTO> blocks;         // cppcheck-suppress unusedStructMember
    std::vector<struct MapPoint> boxes;          // cppcheck-suppress unusedStructMember
    std::vector<struct MapPoint> spawns_player;  // cppcheck-suppress unusedStructMember
    std::vector<struct MapPoint> spawns_items;   // cppcheck-suppress unusedStructMember

    MapInfo(const std::string& name, const struct MapPoint _size, uint8_t _bk):
            mapname(name), size(_size), bk(_bk) {}
};

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
