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

enum ImportedMapObjectType {
    ImportedBlock,
    ImportedSpawnPlayer,
    ImportedSpawnWeapon,
    ImportedBox,
    ImportedDecoration
};

struct ImportedMapObjectData {
    int row;
    int column;
    int zIndex;
    ImportedMapObjectType importedMapObjectType;
    std::string texture;
    
    ImportedMapObjectData(const int _row, const int _col, const int _z,const ImportedMapObjectType type, const std::string& tex)
    :row(_row),column(_col), zIndex(_z), importedMapObjectType(type), texture(tex){}
};

class MapImporter {
protected:
    
    MapReader reader;// cppcheck-suppress unusedStructMember
    
    uint16_t blocks_z;  // cppcheck-suppress unusedStructMember
    uint16_t boxes_z;   // cppcheck-suppress unusedStructMember
    struct MapPoint size;   // cppcheck-suppress unusedStructMember

    std::string boxes_tex;   // cppcheck-suppress unusedStructMember

    std::vector<std::string> textures;              // cppcheck-suppress unusedStructMember
    
    void getBlockObjects(read_seq_t seq, const ImportedMapObjectType type, std::vector<ImportedMapObjectData>& out);
    
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
    std::vector<ImportedMapObjectData> getBlocks();
    std::vector<ImportedMapObjectData> getDecorations() ;
    
    std::vector<ImportedMapObjectData> getPlayerSpawns();
    std::vector<ImportedMapObjectData> getItemSpawns();
    std::vector<ImportedMapObjectData> getBoxes();
};
#endif
