#ifndef LIB_GAMEEVENTS_H
#define LIB_GAMEEVENTS_H

#include <cstdint>
#include "./dtosobject.h"


// No se agrega explosion de granada/destruccion caja
// Se puede manejar desde game event la reproduccion de sonido.
enum SoundEventType : uint8_t {
   //NO_SOUND = 0x00,
   GRENADE_THROW = 0x10,
   BANANA_THROW = 0x11,
   PEWPEW_SHOT = 0x12,
   LASER_SHOT = 0x13, 
   AK47_SHOT = 0x14, 
   DUEL_PISTOL_SHOT = 0x15, 
   COWBOY_SHOT = 0x16, 
   MAGNUM_SHOT = 0x17,
   SHOTGUN_SHOT = 0x18, 
   SNIPER_SHOT = 0x19, 
   
   
   // Podria ser?
   PLAYER_JUMPED = 0x01, 
   PLAYER_DAMAGED = 0x02, 
   PLAYER_PICKUP = 0x03,
   PLAYER_DIED = 0x04, 
   PLAYER_FLAP = 0x05, 
   PLAYER_DROP = 0x06,
   PLAYER_RELOADING = 0x07,
   PLAYER_EQUIP_ARMOR = 0x08,
   PLAYER_EQUIP_HELMET = 0x09,
   
};

enum GameEventType : uint8_t {
   NO_EVENT = 0x00,
   BOX_DESTROYED = 0x01,
   BOMB_EXPLOSION = 0x02,
   GRENADE_EXPLOSION = 0x03,
   BANANA_EXPLOSION = 0x04,
};


struct GameEvent{
    struct MapPoint pos; // cppcheck-suppress unusedStructMember
    GameEventType type;
    
    GameEvent(const coordinate_t _x , const coordinate_t _y, GameEventType _event):pos(_x,_y),type(_event){}
    GameEvent():pos(0,0),type(GameEventType::NO_EVENT){}
};

#endif
