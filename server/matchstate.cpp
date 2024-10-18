#include "./matchstate.h"

#include <iostream>

// Define para cada box que reward tiene.
// Podria ser random ! pero no seria posible de testear.
static const RewardType REWARDS[]{BAZOOKA, CHAINSAW, DEATHRAY, SHOTGUN};

// Step.. advance time by one/iterate logic.
void MatchState::step() {

    // Just step on everybox. And add events.
    for (int boxId = 0; boxId < BOX_COUNT; boxId++) {
        if (boxes[boxId].step()) {  // Re aparecio

            // Agrega el evento de forma no bloqueante..
            // si se pierde se pierde. No deberia haber un maximo.
            observer.receiveEvent(Event(boxId));
        }
    }
}

// Verify if box is available.
bool MatchState::isBoxAvailable(const int box) const {
    return box < BOX_COUNT && box >= 0 && boxes[box].isAvailable();
}

// Intenta hacer que el player abra la caja.
// Si la caja no esta disponible, o a futuro si el player no pudiese. No hara nada.
void MatchState::openBox(const std::string& player, const int box) {
    if (!isBoxAvailable(box)) {
        return;
    }
    // Ignoramos el valor del open.. Ya que ya lo sabemos....
    boxes[box].open(REWARDS[box]);

    observer.receiveEvent(Event(player, REWARDS[box]));
}
