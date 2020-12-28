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
    uint32_t value;
    switch (w) {
    case U8:
        value = cpu.get_memory().get_byte(address, true);
        break;
    case U16:
        value = cpu.get_memory().get_dual(address, true);
        break;
    case U32:
        value = cpu.get_memory().get_quad(address, true);
        break;
    }
    return value;
}

void
MemoryLocation::write(CPU& cpu, Width w, uint32_t value) {
    switch (w) {
    case U8:
        cpu.set_byte(address, value % 256);
        break;
    case U16:
        cpu.get_memory().set_dual(address, value);
        break;
    case U32:
        cpu.get_memory().set_quad(address, value);
        break;
    }
}

void
MemoryLocation::print(Width w) {
    std::cout << "MemoryLocation: ";
    print_quad_in_hex(address);
    std::cout << " ";
}
