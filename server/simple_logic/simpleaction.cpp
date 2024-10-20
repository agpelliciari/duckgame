#include "./simpleaction.h"

#include <iostream>


SimpleAction::SimpleAction(const std::string& name, const uint8_t _boxpicked):
        player(name), boxpicked(_boxpicked) {}

SimpleAction::SimpleAction(): player(), boxpicked(-1) {}


// Double dispatch en cierta medida. Decide que accion en el state se debe aplicar.
// El caso de que sea invalido (box = -1) se handlea en el state... por ahora se ignora.
// Ideal ? no... Pero de la forma que entiendo quieren hacer el tp y sin rebuscarselas
// No hay forma de tener una accion por default que sirva de placeholder para futuras asignaciones.
// Como lamentablemente es necesario por la queue de acciones!
void SimpleAction::applyOn(SimpleState& state) { state.openBox(player, boxpicked); }
