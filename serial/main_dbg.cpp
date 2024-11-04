#include <iostream>
//#include "./serializer.h"
#include <string>

#include "./deserializer.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "No se paso por parametro el archivo target!\n";
        return 1;
    }

    std::string file(argv[1]);

    Deserializer serial(file);

    serial.dosome();
    serial.close();
    serial.close();

    return 0;
}
