

#include "action.h"

Action::Action(): move_action(TypeMoveAction::NONE) {}

void Action::get_move_action(TypeMoveAction& _move_action) {
    _move_action = this->move_action;
}

void Action::still() { this->move_action = TypeMoveAction::NONE; }

void Action::move_right() { this->move_action = TypeMoveAction::MOVE_RIGHT; }

void Action::move_left() { this->move_action = TypeMoveAction::MOVE_LEFT; }

void Action::jump() {
    if (this->move_action == TypeMoveAction::JUMP || this->move_action == TypeMoveAction::FLAP) {
        this->move_action = TypeMoveAction::FLAP;
    } else {
        this->move_action = TypeMoveAction::JUMP;
    }
}

void Action::stay_down() { this->move_action = TypeMoveAction::STAY_DOWN; }
