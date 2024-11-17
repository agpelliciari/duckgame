
#include "box.h"

Box::Box(int x, int y): spawn_point{x, y}, dimension{BOX_SIZE, BOX_SIZE}, spawned(true) {}

Tuple Box::get_spawn_point() {
    return spawn_point;
}

Tuple Box::get_dimension() {
    return dimension;
}

bool Box::is_spawned() {
    return spawned;
}
