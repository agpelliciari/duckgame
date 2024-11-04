#include "./deserializer.h"

#include <fstream>
#include <iostream>


Deserializer::Deserializer(std::string& src): active(true) {

    std::ifstream file(src, std::ios::binary | std::ios::ate);
    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);

    // Se asume es lo suficientemente small para que entre.
    data.reserve(size + 1);
    if (file.read(data.data(), size)) {
        data[size] = 0;
        std::cout << "FILE CONTENT IS ::\n" << std::string(data.data()) << "\n----------END\n";
    } else {
        active = false;
    }
}

bool Deserializer::isactive() { return active.load(); }

void Deserializer::close() {
    if (active.exchange(false)) {
        std::cout << "CLOSED SERIALIZER!!\n";
    } else {
        std::cout << "ALREADY CLOSED SERIALIZER!!\n";
    }
}


void Deserializer::dosome() {
    if (!active) {
        std::cout << "INVALID ALREADY CLOSED\n";
        return;
    }

    ryml::Tree tree = ryml::parse_in_place(data.data());

    ryml::NodeRef bar = tree["map"];
    std::cout << "FIRST IS " << bar[0] << " SECOND IS " << bar[1] << std::endl;

    tree["size_x"] << 20;

    std::cout << "----------- PARSED DATA IS?\n";
    ryml::emit_yaml(tree, stdout);
}
