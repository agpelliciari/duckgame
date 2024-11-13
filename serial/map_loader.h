#ifndef LIB_MAP_LOADER
#define LIB_MAP_LOADER

#include <list>
#include <string>

#include "./map_deserializer.h"


class MapLoader {
protected:
    struct ReferencedMap {
        MapDeserializer deserial;
        int count;
        explicit ReferencedMap(const std::string& name): deserial(name), count(1) {}
    };

    std::list<struct ReferencedMap> maps;  // cppcheck-suppress unusedStructMember

public:
    MapLoader();
    // Asumamos por ahora que no se quiere permitir copias..
    MapLoader(const MapLoader&) = delete;
    MapLoader& operator=(const MapLoader&) = delete;

    // Permitamos el mov... por mas que no sea realmente eficiente.
    MapLoader(MapLoader&&) = delete;
    MapLoader& operator=(MapLoader&&) = delete;

    MapDeserializer& getLoader(const char* mapname);

    void removeLoader(const std::string& loader_id);
};
#endif
