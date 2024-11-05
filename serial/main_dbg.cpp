#include <iostream>
#include <string>

#include "./deserializer.h"
#include "./serializer.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "No se paso por parametro el archivo target!\n";
        return 1;
    }

    std::string file("res/maps/");
    file.append(argv[1]);
    std::cout << "ACT UPON " << file << std::endl;

    Serializer serial(100, 550);

    for (int i = 0; i < 100; i += 3) {
        serial.addTexture(2, 3 + i, GRASS);
    }

    serial.addBox(4, 3);
    serial.addBox(6, 3);
    serial.addBox(6, 4);
    serial.addBox(7, 3);

    serial.addItemSpawn(12, 3);
    serial.addItemSpawn(99, 3);
    serial.addPlayerSpawn(14, 3);
    serial.addPlayerSpawn(23, 3);

    serial.save(file);
    // Deserializer serial(file);

    // serial.dosome();
    // serial.close();
    // serial.close();

    return 0;
}
