#ifndef LIB_BOX_H
#define LIB_BOX_H

#include "common/reward.h"

class SimpleBox {
private:
    // Steps restantes hasta la reaparicion
    int remainingsteps;  // cppcheck-suppress unusedStructMember

public:
    SimpleBox(): remainingsteps(0) {}

    bool isAvailable() const;

    // Ejecuta un step de tiempo. Retorna si re aparecio en este step.
    bool step();

    // Abre, de ser posible.
    // dado el tipo pasado. Bien podria ser random generado adentro.
    Reward open(const RewardType& tipo);
};

#endif
