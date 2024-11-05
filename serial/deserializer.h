#ifndef LIB_DESERIALIZER_H
#define LIB_DESERIALIZER_H

// Tomado de https://github.com/biojppm/rapidyaml/blob/master/samples/quickstart.cpp
#if defined(RYML_SINGLE_HEADER)  // using the single header directly in the executable
#define RYML_SINGLE_HDR_DEFINE_NOW
#include <ryml_all.hpp>
#elif defined(RYML_SINGLE_HEADER_LIB)  // using the single header from a library
#include <ryml_all.hpp>
#else
#include <ryml.hpp>
// <ryml_std.hpp> is needed if interop with std containers is
// desired; ryml itself does not use any STL container.
// For this sample, we will be using std interop, so...
#include <c4/format.hpp>  // needed for the examples below
#include <ryml_std.hpp>   // optional header, provided for std:: interop
#endif

#include <atomic>
#include <cstdint>
#include <string>
#include <vector>

#include "common/dtosobject.h"


class Deserializer {
protected:
    ryml::Tree tree;  // cppcheck-suppress unusedStructMember
    ryml::NodeRef root;

    void readPoints(ryml::NodeRef& list, std::vector<struct MapPoint>& out);

public:
    explicit Deserializer(std::string& src);
    // Asumamos por ahora que no se quiere permitir copias..
    Deserializer(const Deserializer&) = delete;
    Deserializer& operator=(const Deserializer&) = delete;

    // Permitamos el mov... por mas que no sea realmente eficiente.
    Deserializer(Deserializer&&) = delete;
    Deserializer& operator=(Deserializer&&) = delete;

    void dosome();

    struct MapPoint readSize();
    uint8_t readBackground();

    void readBlocks(std::vector<struct BlockDTO>& out);
    void readPlayerSpawns(std::vector<struct MapPoint>& out);
    void readItemSpawns(std::vector<struct MapPoint>& out);
    void readBoxes(std::vector<struct MapPoint>& out);
};
#endif
