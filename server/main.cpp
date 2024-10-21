#include <cstring>
#include <iostream>
#include <string>

#include <arpa/inet.h>

#include "common/core/liberror.h"
#include "common/core/resolvererror.h"
#include "server/gameerror.h"
#include "server/server.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "No se paso por parametro el servicio/puerto para el servidor\n";
        return 1;
    }

    try {

        Server server(argv[1]);

        server.initmatch();  // Starts async.

        server.waitclose();

        return 0;
    } catch (const LibError& error) {
        std::cerr << "Internal error: " << error.what() << std::endl;
        return 1;
    } catch (const ResolverError& error) {
        std::cerr << "Resolve: " << error.what() << std::endl;
        return 1;
    }


    return 0;
}
