#include "ui_loop.h"

#include <iostream>
#include <exception>

#include <SDL2pp/SDL2pp.hh>
#include <SDL2/SDL.h>

using namespace SDL2pp;

int main() try {

	UILoop uiLoop;

	while (uiLoop.isRunning()) {
		uiLoop.handleEvent();
		uiLoop.update();
		uiLoop.draw();
	}
	
	return 0;
} catch (std::exception& e) {
	// If case of error, print it and exit with error
	std::cerr << e.what() << std::endl;
	return 1;
}
