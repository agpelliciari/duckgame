
#include "weapon.h"

Weapon::Weapon():type(TypeWeapon::NONE){}

void Weapon::get_weapon(TypeWeapon &type){
    this->type = type;
}
