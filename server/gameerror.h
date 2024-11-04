#ifndef GAME_ERROR_H
#define GAME_ERROR_H

#include <exception>

#include "common/errors.h"

// typedef uint8_t game_error_type;
typedef LobbyErrorType game_error_type;
/*
 * Clase para encapsular el `errno` de C, "el ultimó error".
 * Es una excepción genérica que se encarga de los detalles
 * de decodificar el `errno` en un mensaje más entendible.
 * */
class GameError: public std::exception {
    // cppcheck-suppress unusedStructMember
    game_error_type err_code;  // Codigo de error interno.

    // cppcheck-suppress unusedStructMember
    char msg_error[256];  // Si se usa, falso positivo.

public:
    /*
     * Dado que `errno` es una variable global y puede ser modificada por
     * cualquier función, hay que hacer una copia apenas se haya detectado
     * el error, para luego lanzar `GameError` o bien lanzar `GameError` apenas
     * ya se haya detectado el error.
     *
     * El constructor `GameError` es variadico y recibe, ademas del `errno`,
     * un format-string (como `printf`) y cero o más argumentos que
     * formaran parte del mensaje.
     *
     * int ret = foo();
     * if (ret == -1)
     *      throw GameError(errno, "The function %s has failed: ", "foo");
     *  */
    GameError(game_error_type code, const char* fmt, ...) noexcept;

    game_error_type get_code() const;

    virtual const char* what() const noexcept override;

    virtual ~GameError();
};

#endif
