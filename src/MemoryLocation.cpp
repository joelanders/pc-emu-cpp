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

bool
MemoryLocation::write(CPU& cpu, Width w, uint32_t value) {
    std::cout << "mem loc write() to addy ";
    print_quad_in_hex(address);
    std::cout << "value ";
    print_quad_in_hex(value);
    std::cout << " width ";
    print_width(w);
    printf("\n");
    cpu.set_byte(address, value % 256);
    return true;
}

void
MemoryLocation::print() {
    std::cout << "MemoryLocation: ";
    print_quad_in_hex(address);
    std::cout << " ";
}
