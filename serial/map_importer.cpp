#include "./map_importer.h"
#include <iostream>

MapImporter::MapImporter(const std::string& src): reader(src),blocks_z(0), boxes_z(0){

    std::cout << "GOT TO START READING?\n";
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




std::vector<ImportedMapObjectData> MapImporter::getDecorations(){
    read_seq_t decorations = reader.getDecorations();
    std::vector<ImportedMapObjectData> res;
    
    
    int size = decorations.num_children();
    res.reserve(size);

    for (int i = 0; i < size; i++) {
        struct MapPoint pos;
        uint16_t zIndex;
        uint8_t tex_id;
        
        read_item_t item = decorations[i];
        reader.assertIsMap(item);
        
        reader.readItemPosition(item, pos);
        reader.readItemTexture(item, tex_id);
        reader.readItemZInd(item, zIndex);
        
        res.emplace_back(pos.y,pos.x, zIndex, ImportedDecoration, textures[tex_id]);
    }
    
    return res;
}

std::vector<ImportedMapObjectData> MapImporter::getBoxes(){
    read_seq_t boxes = reader.getBoxes();
    std::vector<ImportedMapObjectData> res;
    
    
    int size = boxes.num_children();
    res.reserve(size);

    for (int i = 0; i < size; i++) {
        struct MapPoint pos;
        
        read_item_t item = boxes[i];
        reader.assertIsMap(item);

        reader.readItemPosition(item, pos);
        
        res.emplace_back(pos.y,pos.x, boxes_z, ImportedBox, boxes_tex);
    }
    
    return res;
}

void MapImporter::getBlockObjects(read_seq_t seq, const ImportedMapObjectType type, std::vector<ImportedMapObjectData>& res){
    int size = seq.num_children();
    res.reserve(size);
    for (int i = 0; i < size; i++) {
        struct MapPoint pos;
        uint8_t tex_id;
        read_item_t item = seq[i];
        reader.assertIsMap(item);
        
        reader.readItemPosition(item, pos);
        reader.readItemTexture(item, tex_id);
        
        res.emplace_back(pos.y,pos.x, blocks_z, type, textures[tex_id]);
    }    
}


std::vector<ImportedMapObjectData> MapImporter::getPlayerSpawns(){
    std::vector<ImportedMapObjectData> res;
    getBlockObjects(reader.getPlayerSpawns(), ImportedSpawnPlayer, res);
    return res;
}

std::vector<ImportedMapObjectData> MapImporter::getItemSpawns(){
    std::vector<ImportedMapObjectData> res;
    getBlockObjects(reader.getItemSpawns(), ImportedSpawnWeapon, res);
    return res;
}

std::vector<ImportedMapObjectData> MapImporter::getBlocks(){
    std::vector<ImportedMapObjectData> res;
    getBlockObjects(reader.getBlocks(), ImportedBlock, res);
    return res;
}

