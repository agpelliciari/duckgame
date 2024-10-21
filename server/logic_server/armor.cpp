
#include "armor.h"

Armor::Armor(): equipped(false) {}

void Armor::equipp() { this->equipped = true; }

void Armor::is_equipped(const bool& equipped_) { this->equipped = equipped_; }
