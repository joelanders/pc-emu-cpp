//
// Created by Joe Landers on 23.05.20.
//

#include "MemoryLocation.h"

MemoryLocation::MemoryLocation(uint32_t addy) {
    std::cout << "mem loc constructor with address =  ";
    print_quad_in_hex(addy);
    printf("\n");
    address = addy;
}

uint32_t
MemoryLocation::read(CPU& cpu, Width w) {
    std::cout << "mem loc read() from ";
    print_quad_in_hex(address);
    auto b = cpu.get_memory().get_byte(address);
    std::cout << "value is ";
    print_byte_in_hex(b);
    printf("\n");
    return b;
}

uint32_t
MemoryLocation::write(CPU& cpu, Width w, uint32_t value) {
    std::cout << "mem loc write() to addy ";
    print_quad_in_hex(address);
    std::cout << "value ";
    print_quad_in_hex(value);
    printf("\n");
    cpu.set_byte(address, value % 256);
    return 0x69;
}
