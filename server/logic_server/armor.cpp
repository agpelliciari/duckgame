
#include "armor.h"

Armor::Armor():equipped(false){}

void Armor::equipp(){
    this->equipped = true;
}

void Armor::is_equipped(bool &equipped_){
    this->equipped = equipped_;
}
