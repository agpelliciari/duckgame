#include <exception>
#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>

#include "ui_loop.h"

int main() try { return 0; } catch (std::exception& e) {
    // If case of error, print it and exit with error
    std::cerr << e.what() << std::endl;
    return 1;
}
