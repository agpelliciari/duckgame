#ifndef LIB_LEVEL_FIELDS
#define LIB_LEVEL_FIELDS

class LevelFields {
public:
    static const char* SIZE_X;
    static const char* SIZE_Y;
    static const char* BACKGROUND;
    static const char* TEXTURES;
    static const char* BOXES;
    static const char* ITEM_SPAWNS;
    static const char* PLAYER_SPAWNS;
};
const char* LevelFields::SIZE_X = "size_x";
const char* LevelFields::SIZE_Y = "size_y";
const char* LevelFields::BACKGROUND = "background";
const char* LevelFields::TEXTURES = "textures";
const char* LevelFields::BOXES = "boxes";
const char* LevelFields::ITEM_SPAWNS = "spawns_item";
const char* LevelFields::PLAYER_SPAWNS = "spawns_player";


#endif
