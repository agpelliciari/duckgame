

#ifndef COORDINATES_H
#define COORDINATES_H



class Coordinates {

    private:
        int initial_x;
        int initial_y;
        int actual_x;
        int actual_y;
        int step;

    public:
        Coordinates(int x, int y);

        void get_coordinates(int &x, int &y);

        void move_right();
        void move_left();
        void jump();

};



#endif //COORDINATES_H
