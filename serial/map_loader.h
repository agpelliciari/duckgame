#ifndef LIB_MAP_LOADER
#define LIB_MAP_LOADER

#include "./map_deserializer.h"


class MapLoader {
protected:
public:
    MapLoader();
    // Asumamos por ahora que no se quiere permitir copias..
    MapLoader(const MapLoader&) = delete;
    MapLoader& operator=(const MapLoader&) = delete;

    // Permitamos el mov... por mas que no sea realmente eficiente.
    MapLoader(MapLoader&&) = delete;
    MapLoader& operator=(MapLoader&&) = delete;

    void loadMap(const char* mapname);
};
#endif
