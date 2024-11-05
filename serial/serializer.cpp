#include "./serializer.h"

#include <iostream>

bool Serializer::isactive() { return active.load(); }

void Serializer::close() {
    if (active.exchange(false)) {
        std::cout << "CLOSED SERIALIZER!!\n";
    } else {
        std::cout << "ALREADY CLOSED SERIALIZER!!\n";
    }
}


void Serializer::dosome() {
    char yml_buf[] = "{foo: 1, bar: [2, 3], john: doe}";
    ryml::Tree tree = ryml::parse_in_place(yml_buf);

    ryml::NodeRef bar = tree["bar"];
    std::cout << "FIRST IS " << bar[0] << " SECOND IS " << bar[1] << std::endl;

    tree["foo"] << "Some foo data";

    std::cout << "----------- PARSED DATA IS?\n";
    ryml::emit_yaml(tree, stdout);
}
