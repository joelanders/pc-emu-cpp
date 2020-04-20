#include <cstdio>
#include <iostream>

#include "config.h"
#include "mylib.h"

int main(int argc, char** argv) {
    printf("program version: %i.%i.%i\n", VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH);
    printf("git hash: %s\n", GIT_REVISION);

    CPU cpu;
    std::cout << cpu << std::endl;

    cpu.get_memory().set_bytes(0, "0a aa 0b bb");
    std::cout << cpu << std::endl;

    return 0;
}
