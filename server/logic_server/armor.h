

#ifndef ARMOR_H
#define ARMOR_H


class Armor {

private:
    bool equipped;  // cppcheck-suppress unusedStructMember

public:
    Armor();
    void equipp();
    void is_equipped(const bool& equipped);
};


#endif  // ARMOR_H
