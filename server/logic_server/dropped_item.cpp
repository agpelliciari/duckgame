

#include "dropped_item.h"

DroppedItem::DroppedItem(std::unique_ptr<Weapon> weapon_,
                         int position_x, int position_y, int dimension_x, int dimension_y):
                        alive(true), position(position_x, position_y), dimension(dimension_x,dimension_y),
                        weapon(std::move(weapon_)){}

Tuple DroppedItem::get_position(){
    return position;
}

Tuple DroppedItem::get_dimension(){
    return dimension;
}

bool DroppedItem::is_alive(){
    return alive;
}

bool DroppedItem::is_on_range(int player_position_x, int player_position_y){
    return (player_position_x >= position.x && player_position_x <= position.x + dimension.x &&
                player_position_y >= position.y && player_position_y <= position.x + dimension.y);
}

std::unique_ptr<Weapon> DroppedItem::get_weapon(){
    if (alive){
        alive = false;
        auto weapon_ = std::move(this->weapon);
        this -> weapon = nullptr;
        return weapon_;
    }
    return nullptr;
}

void DroppedItem::get_data(int &position_x_, int &position_y_, TypeDynamicObject &object_){
    position_x_ = position.x;
    position_y_ = position.y;
    weapon->get_type(object_);
}
