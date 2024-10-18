#include "client/client.h"

#include <cstring>
#include <iostream>
#include <string>

#include "common/liberror.h"

#define ASK_NAME "What is your name?"
#define ACTION_EXIT "Exit"
#define ACTION_PICKUP "Pickup"
#define ACTION_READ "Read"

unsigned int Client::inputnum() {
    unsigned int res;
    if (!(std::cin >> res)) {
        throw LibError(1, "Could not read number argument");
    }

    return res;
}

void Client::listenActions() {
    // Un buffer lo suficientemente grande. Que esta en el stack.

    std::cout << ASK_NAME << std::endl;

    std::string name;
    if (!(std::getline(std::cin, name, '\n'))) {  // Could not read name.
        throw LibError(1, "Could not read player name");
    }

    std::string action;

    while (std::cin >> action) {
        if (action.compare(ACTION_EXIT) == 0) {
            return;
        }
        if (action.compare(ACTION_PICKUP) == 0) {
            uint8_t box = inputnum();  // Se valida en el server.
            protocol.pickup(name, box);
            continue;
        }

        if (action.compare(ACTION_READ) == 0) {
            int count = inputnum();

            while (count > 0) {
                std::cout << protocol.recvevent().parseinfo() << std::endl;
                count -= 1;
            }
            continue;
        }

        std::cerr << "NOT RECOGNIZED: " << action << std::endl;
    }
}
