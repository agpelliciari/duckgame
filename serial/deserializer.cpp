#include "./deserializer.h"

#include <fstream>
#include <iostream>


Deserializer::Deserializer(std::string& src): active(true) {

    std::ifstream file(src, std::ios::binary | std::ios::ate);
    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);

    // Se asume es lo suficientemente small para que entre.
    std::vector<char> map;
    map.reserve(size + 1);
    if (file.read(map.data(), size)) {
        map[size] = 0;
        tree = ryml::parse_in_place(map.data());
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


    ryml::NodeRef blocks = tree["textures"];
    std::cout << "WIDTH IS " << tree["size_x"] << " HEIGHT IS " << tree["size_y"]
              << " count blocks " << blocks.num_children() << std::endl;
}
