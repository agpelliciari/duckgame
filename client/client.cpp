#include <cstdint>
#include <cstring>
#include <iostream>
#include <string>

#include "client_src/client.h"
#include "common_src/liberror.h"
#include "common_src/resolvererror.h"

static const char* const KnifeValues[] = {"No", "Yes"};

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "No se paso los parametros el <host> <servicio> de con quien conectar\n";
        return 1;
    }

    try {
        char* host = NULL;
        char* service = argv[1];
        if (argc > 2) {
            host = argv[1];
            service = argv[2];
        }

        Client client(host, service);

        client.listenActions();

        return 0;
    } catch (const LibError& error) {
        std::cerr << "Internal error: " << error.what() << std::endl;
        return 1;
    } catch (const ResolverError& error) {
        std::cerr << "Resolve: " << error.what() << std::endl;
        return 1;
    }
}
