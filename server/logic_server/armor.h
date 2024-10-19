

#ifndef ARMOR_H
#define ARMOR_H



class Armor {

    private:
        bool equipped;

    public:
        Armor();
        void equipp();
        void is_equipped(bool &equipped);

};



#endif //ARMOR_H
