#include "./map_importer.h"

MapImporter::MapImporter(const std::string& src): reader(src),blocks_z(0), boxes_z(0){
    
    // Lee informacion que sera usada recurrentemente.
    reader.readBlocksZ(blocks_z);
    reader.readBoxesZ(boxes_z);
    reader.readBoxesTexture(boxes_tex);
    reader.readTextures(textures);
    reader.readSize(size);    
}

// Metodos delegatorios. Capaz no haria falta exponerlos en esta clase.
int MapImporter::getWidth() const{
     return size.x;
}
int MapImporter::getHeight() const{
     return size.y;
}

std::string MapImporter::getBackground() {
     std::string background;
     reader.readBackground(background);
     return background;
}



std::vector<MapObjectData> MapImporter::getBlocks(){
    read_seq_t blocks = reader.getBlocks();
    std::vector<MapObjectData> res;
    
    
    int size = blocks.num_children();
    res.reserve(size);

    for (int i = 0; i < size; i++) {
        struct MapPoint pos;
        uint8_t tex_id;
        
        read_item_t item = blocks[i];
        
        reader.readItemPosition(item, pos);
        reader.readItemTexture(item, tex_id);
        
        res.emplace_back(pos.y,pos.x, blocks_z, Block, textures[tex_id]);
    }
    
    return res;
}


std::vector<MapObjectData> MapImporter::getDecorations(){
    read_seq_t decorations = reader.getDecorations();
    std::vector<MapObjectData> res;
    
    
    int size = decorations.num_children();
    res.reserve(size);

    for (int i = 0; i < size; i++) {
        struct MapPoint pos;
        uint16_t zIndex;
        uint8_t tex_id;
        
        read_item_t item = decorations[i];
        
        reader.readItemPosition(item, pos);
        reader.readItemTexture(item, tex_id);
        reader.readItemZInd(item, zIndex);
        
        res.emplace_back(pos.y,pos.x, zIndex, Decoration, textures[tex_id]);
    }
    
    return res;
}

std::vector<MapObjectData> MapImporter::getBoxes(){
    read_seq_t boxes = reader.getBlocks();
    std::vector<MapObjectData> res;
    
    
    int size = boxes.num_children();
    res.reserve(size);

    for (int i = 0; i < size; i++) {
        struct MapPoint pos;
        
        read_item_t item = boxes[i];
        
        reader.readItemPosition(item, pos);
        
        res.emplace_back(pos.y,pos.x, blocks_z, Box, boxes_tex);
    }
    
    return res;



}


std::vector<MapObjectData> MapImporter::getPlayerSpawns(){
    read_seq_t spawns = reader.getPlayerSpawns();
    std::vector<MapObjectData> res;
    
    
    int size = spawns.num_children();
    res.reserve(size);
    
    return res;
}

std::vector<MapObjectData> MapImporter::getItemSpawns(){
    read_seq_t spawns = reader.getItemSpawns();
    std::vector<MapObjectData> res;
    
    int size = spawns.num_children();
    res.reserve(size);
    
    return res;
}

