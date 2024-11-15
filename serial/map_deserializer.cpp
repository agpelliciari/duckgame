#include "./map_deserializer.h"

#include <fstream>
#include <iostream>

#include "common/core/liberror.h"

MapDeserializer::MapDeserializer(const std::string& src): srcmap(src), reader(srcmap) {
}

// Metodos delegatorios. Capaz no haria falta exponerlos en esta clase.
void MapDeserializer::readSize(struct MapPoint& size) {
     reader.readSize(size);
}

void MapDeserializer::readBackground(std::string& background) {
     reader.readBackground(background);
}

void MapDeserializer::readBlocksZ(uint16_t& z) { 
     reader.readBlocksZ(z);
}

void MapDeserializer::readBoxesZ(uint16_t& z) {
     reader.readBoxesZ(z);
}

void MapDeserializer::readBoxesTexture(std::string& box_tex) {
     reader.readBoxesTexture(box_tex);
}


void MapDeserializer::readTextures(std::vector<std::string>& res) {
     reader.readTextures(res);
}




// Metodos especificos para el cargado para el server.
const std::string& MapDeserializer::getMapName() const { return srcmap; }

void MapDeserializer::readDecorations(std::vector<struct DecorationDTO>& res) {
    const ryml::NodeRef& decorations = reader.getDecorations();
    
    int size = decorations.num_children();
    res.reserve(size);

    for (int i = 0; i < size; i++) {
        const ryml::ConstNodeRef& item = decorations[i];
        DecorationDTO& decoration = res.emplace_back();
        
        reader.readItemPosition(item, decoration.pos);
        reader.readItemTexture(item, decoration.texture_id);
        reader.readItemZInd(item, decoration.z_ind);
    }
}


void MapDeserializer::readBlocks(std::vector<struct BlockDTO>& res) {
    const ryml::NodeRef& blocks = reader.getBlocks();
    
    int size = blocks.num_children();
    res.reserve(size);

    for (int i = 0; i < size; i++) {
        const ryml::ConstNodeRef& item = blocks[i];
        BlockDTO& block = res.emplace_back();
        
        reader.readItemPosition(item, block.pos);
        reader.readItemTexture(item, block.texture_id);
        //reader.readItemZInd(item, block.z_ind);
    }
}

void MapDeserializer::readPlayerSpawns(std::vector<struct MapPoint>& res) {
    reader.readPoints(reader.getPlayerSpawns(), res);
}
void MapDeserializer::readItemSpawns(std::vector<struct MapPoint>& res) {
    reader.readPoints(reader.getItemSpawns(), res);
}

void MapDeserializer::readBoxes(std::vector<struct MapPoint>& res) {
    reader.readPoints(reader.getBoxes(), res);
}


void MapDeserializer::loadMapInfo(struct MapInfo& info) {
    reader.readSize(info.size);

    reader.readBlocksZ(info.blocks_z);
    reader.readBoxesZ(info.boxes_z);

    reader.readBackground(info.background);
    reader.readBoxesTexture(info.boxes_tex);

    reader.readTextures(info.textures);
    readBlocks(info.blocks);
    readDecorations(info.decorations);

    info.map_id = srcmap;
}


void MapDeserializer::loadObjectsInfo(struct ObjectsInfo& info) {
    readPlayerSpawns(info.player_spawns);
    readItemSpawns(info.item_spawns);
    readBoxes(info.boxes);

    // Read blocks .. again? NAA
}
