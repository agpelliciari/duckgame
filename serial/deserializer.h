#ifndef LIB_DESERIALIZER_H
#define LIB_DESERIALIZER_H

#include <atomic>
#include <cstdint>
#include <string>
#include <vector>


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


class Deserializer {
protected:
    std::atomic<bool> active;  // cppcheck-suppress unusedStructMember
    ryml::Tree tree;           // cppcheck-suppress unusedStructMember
public:
    explicit Deserializer(std::string& src);
    // Asumamos por ahora que no se quiere permitir copias..
    Deserializer(const Deserializer&) = delete;
    Deserializer& operator=(const Deserializer&) = delete;

    // Permitamos el mov... por mas que no sea realmente eficiente.
    Deserializer(Deserializer&&) = delete;
    Deserializer& operator=(Deserializer&&) = delete;


    void dosome();
    bool isactive();  // Se fija si esta activo, pudo ser cerrado como nunca haber sido activo.
    void close();
};
#endif
