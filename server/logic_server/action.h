

#ifndef ACTION_H
#define ACTION_H
#include "common/dtosplayer.h"



class Action {

    private:
        TypeMoveAction move_action;

    public:
        Action();
        void get_move_action(TypeMoveAction& _move_action);
        void move_right();
        void move_left();
        void jump();
        void stay_down();
};



#endif //ACTION_H
