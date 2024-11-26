#ifndef LIB_GAMEEVENTS_H
#define LIB_GAMEEVENTS_H

#include <cstdint>
#include "./dtosobject.h"

enum GameEventType : uint8_t {
   NO_EVENT = 0x00,
   BOX_DESTROYED = 0x01,
   BOMB_EXPLOSION = 0x02,
   // Se podria tambien poner aca
   //PLAYER_JUMPED, // o asi.
};


struct GameEvent{
    struct MapPoint pos; // cppcheck-suppress unusedStructMember
    GameEventType type;
    
    GameEvent(const coordinate_t _x , const coordinate_t _y, GameEventType _event):pos(_x,_y),type(_event){}
    GameEvent():pos(0,0),type(NO_EVENT){}
};

#endif
