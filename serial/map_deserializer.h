#ifndef LIB_MAPDESERIALIZER_H
#define LIB_MAPDESERIALIZER_H

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

#include "common/dtosmap.h"


/*
void EditorWindow::importFromFileSystem() {
    MapDeserializer deserial("./res/maps/map3.yaml");

    const std::string background = serial.getBackground();

    const std::vector<MapObjectData> blocks = serial.getBlocks();
    const std::vector<MapObjectData> spawnPlayers = serial.getPlayerSpawns();
    const std::vector<MapObjectData> spawnWeapons = serial.getItemSpawns();
    const std::vector<MapObjectData> boxes = serial.getBoxes();
    const std::vector<MapObjectData> decorations = serial.getDecorations();
}
struct MapObjectData {
    int row;
    int column;
    int zIndex;
    MapObjectType mapObjectType;
    std::string texture;
};
enum MapObjectType {
    Block,
    SpawnPlayer,
    SpawnWeapon,
    Box,
    Decoration
};
*/
class MapDeserializer {
protected:
    std::string srcmap;  // cppcheck-suppress unusedStructMember

    ryml::Tree tree;  // cppcheck-suppress unusedStructMember
    ryml::NodeRef root;

    void readPoints(ryml::NodeRef& list, std::vector<struct MapPoint>& out);

public:
    explicit MapDeserializer(const std::string& src);
    // Asumamos por ahora que no se quiere permitir copias..
    MapDeserializer(const MapDeserializer&) = delete;
    MapDeserializer& operator=(const MapDeserializer&) = delete;

    // Permitamos el mov... por mas que no sea realmente eficiente.
    MapDeserializer(MapDeserializer&&) = delete;
    MapDeserializer& operator=(MapDeserializer&&) = delete;

    const std::string& getMapName() const;


    // Loadings inplace for data.
    void readSize(struct MapPoint& size);
    void readBackground(std::string& background);

    void readBlocksZ(uint16_t& blocks_z);

    void readBoxesZ(uint16_t& boxes_z);
    void readBoxesTexture(std::string& box_tex);

    void readTextures(std::vector<std::string>& out);

    void readBlocks(std::vector<struct BlockDTO>& out);
    void readDecorations(std::vector<struct DecorationDTO>& out);

    void readPlayerSpawns(std::vector<struct MapPoint>& out);
    void readItemSpawns(std::vector<struct MapPoint>& out);
    void readBoxes(std::vector<struct MapPoint>& out);


    // General methods que encapsulan multiples acciones.
    void loadMapInfo(struct MapInfo& info);
    void loadObjectsInfo(struct ObjectsInfo& info);
};
#endif
