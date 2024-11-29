#ifndef LIB_GAMEEVENTS_H
#define LIB_GAMEEVENTS_H

#include <cstdint>
#include "./dtosobject.h"


// No se agrega explosion de granada/destruccion caja
// Se puede manejar desde game event la reproduccion de sonido.
enum SoundEventType : uint8_t {
   //NO_SOUND = 0x00,
   PLAYER_JUMPED = 0x03, 
   PLAYER_DAMAGED = 0x04, 
   GUN_SHOT = 0x05, 
   PLAYER_PICKUP = 0x08,
   
   // Podria ser?
   PLAYER_DIED = 0x07, 
   PLAYER_FLAP = 0x06, 
   PLAYER_DROP = 0x09,
   
};

enum GameEventType : uint8_t {
   NO_EVENT = 0x00,
   BOX_DESTROYED = 0x01,
   BOMB_EXPLOSION = 0x02,
};


struct GameEvent{
    struct MapPoint pos; // cppcheck-suppress unusedStructMember
    GameEventType type;
    
    GameEvent(const coordinate_t _x , const coordinate_t _y, GameEventType _event):pos(_x,_y),type(_event){}
    GameEvent():pos(0,0),type(GameEventType::NO_EVENT){}
};

#endif
