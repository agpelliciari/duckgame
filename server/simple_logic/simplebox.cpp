#include "./simplebox.h"

#include <iostream>
#include <string>

#include "server/gameerror.h"

bool SimpleBox::isAvailable() const { return remainingsteps == 0; }

Reward SimpleBox::open(const RewardType& type) {
    if (!isAvailable()) {
        throw GameError("Tried to open not available box");
    }
    Reward res(type);

    remainingsteps = res.respawntime();
    return res;
}

bool SimpleBox::step() {
    if (!isAvailable()) {
        remainingsteps -= 1;
        return isAvailable();
    }
    return false;
}
