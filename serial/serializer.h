#ifndef LIB_SERIALIZER_H
#define LIB_SERIALIZER_H

#include <atomic>
#include <cstdint>

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


class Serializer {
protected:
    std::atomic<bool> active;  // cppcheck-suppress unusedStructMember
public:
    Serializer(): active(true) {}
    // Asumamos por ahora que no se quiere permitir copias..
    Serializer(const Serializer&) = delete;
    Serializer& operator=(const Serializer&) = delete;

    // Permitamos el mov... por mas que no sea realmente eficiente.
    Serializer(Serializer&&) = delete;
    Serializer& operator=(Serializer&&) = delete;


    void dosome();
    bool isactive();  // Se fija si esta activo, pudo ser cerrado como nunca haber sido activo.
    void close();
};
#endif
