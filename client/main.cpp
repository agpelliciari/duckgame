#include "client.h"

#include <iostream>

constexpr int ERROR_CODE = 1;

int main(int argc, char* argv[]) {
    try {
		Client client(argc, argv);
		return client.exec();
    } catch (const std::exception& err) {
        std::cerr << "Something went wrong and an exception was caught: " << err.what() << "\n";
        return ERROR_CODE;
    } catch (...) {
        std::cerr << "Something went wrong and an unknown exception was caught.\n";
        return ERROR_CODE;
    }
}
