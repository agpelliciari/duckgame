#ifndef LIB_MATCH_ACTION_H
#define LIB_MATCH_ACTION_H

#include <cstdint>
#include <string>

#include "./matchstate.h"

// Encapsulador de logica de una accion de un player.
// Por ahora solo un pickup.
class MatchAction {
private:
    std::string player;  // cppcheck-suppress unusedStructMember
    int boxpicked;       // cppcheck-suppress unusedStructMember

public:
    // Para abstraer el socket se tiene solo un constructor que construye el socket internamente.
    explicit MatchAction(const std::string& name, const uint8_t boxpicked);
    MatchAction();

    // Asumamos copy = default, move = default
    MatchAction(const MatchAction&) = default;
    MatchAction& operator=(const MatchAction&) = default;
    MatchAction(MatchAction&&) = default;
    MatchAction& operator=(MatchAction&&) = default;

    // Decide y delega que accion aplicar al state del match.
    void applyOn(MatchState& state);
};

#endif
