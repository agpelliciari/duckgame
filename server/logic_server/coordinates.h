

#ifndef COORDINATES_H
#define COORDINATES_H


class Coordinates {

private:
    int initial_x;  // cppcheck-suppress unusedStructMember
    int initial_y;  // cppcheck-suppress unusedStructMember
    int actual_x;   // cppcheck-suppress unusedStructMember
    int actual_y;   // cppcheck-suppress unusedStructMember
    int step;       // cppcheck-suppress unusedStructMember
    float speed_y;  // cppcheck-suppress unusedStructMember
    float gravity;  // cppcheck-suppress unusedStructMember
    int time; // cppcheck-suppress unusedStructMember

public:
    Coordinates(int x, int y);
    void get_coordinates(int& x, int& y);
    void move_right();
    void move_left();
    void jump();
    void update_position_y();
    void update_time();

};


#endif  // COORDINATES_H
