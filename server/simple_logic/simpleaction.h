#ifndef LIB_SIMPLE_ACTION_H
#define LIB_SIMPLE_ACTION_H

#include <cstdint>
#include <string>

#include "./simplestate.h"

// Encapsulador de logica de una accion de un player.
// Por ahora solo un pickup.
class SimpleAction {
private:
    std::string player;  // cppcheck-suppress unusedStructMember
    int boxpicked;       // cppcheck-suppress unusedStructMember

public:
    // Para abstraer el socket se tiene solo un constructor que construye el socket internamente.
    explicit SimpleAction(const std::string& name, const uint8_t boxpicked);
    SimpleAction();

    // Asumamos copy = default, move = default
    SimpleAction(const SimpleAction&) = default;
    SimpleAction& operator=(const SimpleAction&) = default;
    SimpleAction(SimpleAction&&) = default;
    SimpleAction& operator=(SimpleAction&&) = default;

    // Decide y delega que accion aplicar al state del match.
    void applyOn(SimpleState& state);
};

#endif
