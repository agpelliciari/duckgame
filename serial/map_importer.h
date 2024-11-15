#ifndef LIB_MapImporter_H
#define LIB_MapImporter_H

// Tomado de https://github.com/biojppm/rapidyaml/blob/master/samples/quickstart.cpp
#if defined(RYML_SINGLE_HEADER)  // using the single header directly in the executable
#define RYML_SINGLE_HDR_DEFINE_NOW
#include <ryml_all.hpp>
#elif defined(RYML_SINGLE_HEADER_LIB)  // using the single header from a library
#include <ryml_all.hpp>
#else
#include <ryml.hpp>
// <ryml_std.hpp> is needed if interop with std containers is
// desired; ryml itself does not use any STL container.
// For this sample, we will be using std interop, so...
#include <c4/format.hpp>  // needed for the examples below
#include <ryml_std.hpp>   // optional header, provided for std:: interop
#endif

#include <atomic>
#include <cstdint>
#include <string>
#include <vector>

#include "./map_reader.h"

enum MapObjectType {
    Block,
    SpawnPlayer,
    SpawnWeapon,
    Box,
    Decoration
};

struct MapObjectData {
    int row;
    int column;
    int zIndex;
    MapObjectType mapObjectType;
    std::string texture;
    
    MapObjectData(const int _row, const int _col, const int _z,const MapObjectType type, const std::string& tex)
    :row(_row),column(_col), zIndex(_z), mapObjectType(type), texture(tex){}
};

/*
void EditorWindow::importFromFileSystem() {
    MapImporter deserial("./res/maps/map3.yaml");

    const std::string background = serial.getBackground();

    const std::vector<MapObjectData> blocks = serial.getBlocks();
    const std::vector<MapObjectData> spawnPlayers = serial.getPlayerSpawns();
    const std::vector<MapObjectData> spawnWeapons = serial.getItemSpawns();
    const std::vector<MapObjectData> boxes = serial.getBoxes();
    const std::vector<MapObjectData> decorations = serial.getDecorations();
}

*/
class MapImporter {
protected:
    
    MapReader reader;// cppcheck-suppress unusedStructMember
    
    uint16_t blocks_z;  // cppcheck-suppress unusedStructMember
    uint16_t boxes_z;   // cppcheck-suppress unusedStructMember
    struct MapPoint size;   // cppcheck-suppress unusedStructMember

    std::string boxes_tex;   // cppcheck-suppress unusedStructMember

    std::vector<std::string> textures;              // cppcheck-suppress unusedStructMember
    
public:
    explicit MapImporter(const std::string& src);
    // Asumamos por ahora que no se quiere permitir copias..
    MapImporter(const MapImporter&) = delete;
    MapImporter& operator=(const MapImporter&) = delete;

    // Permitamos el mov... por mas que no sea realmente eficiente.
    MapImporter(MapImporter&&) = delete;
    MapImporter& operator=(MapImporter&&) = delete;
    

    
    // Especificos para el editor
    int getWidth() const;
    int getHeight() const;
    
    std::string getBackground() ;
    std::vector<MapObjectData> getBlocks();
    std::vector<MapObjectData> getDecorations() ;
    
    std::vector<MapObjectData> getPlayerSpawns();
    std::vector<MapObjectData> getItemSpawns();
    std::vector<MapObjectData> getBoxes();
};
#endif
