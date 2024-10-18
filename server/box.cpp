#include "./box.h"

#include <iostream>
#include <string>

#include "./gameerror.h"

bool Box::isAvailable() const { return remainingsteps == 0; }

Reward Box::open(const RewardType& type) {
    if (!isAvailable()) {
        throw GameError(1, "Tried to open not available box");
    }
    Reward res(type);

    remainingsteps = res.respawntime();
    return res;
}

bool Box::step() {
    if (!isAvailable()) {
        remainingsteps -= 1;
        return isAvailable();
    }
    return false;
}
