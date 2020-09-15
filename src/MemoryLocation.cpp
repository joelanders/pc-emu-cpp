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
    case U32:
        // value = cpu.get_memory().get_byte(address, true);
        // value += cpu.get_memory().get_byte(address + 1, true) << 8;
        // value += cpu.get_memory().get_byte(address + 2, true) << 16;
        // value += cpu.get_memory().get_byte(address + 3, true) << 24;
        value = cpu.get_memory().get_quad(address, true);
        break;
    }
    // std::cout << "MEMGET offset: ";
    // print_quad_in_hex(address);
    // std::cout << "value: ";
    // print_quad_in_hex(value);
    // std::cout << "width is ";
    // print_width(w);
    // printf("\n");
    return value;
}

void
MemoryLocation::write(CPU& cpu, Width w, uint32_t value) {
    // std::cout << "MEMSET offset: ";
    // print_quad_in_hex(address);
    // std::cout << "value: ";
    // print_quad_in_hex(value);
    // std::cout << " width ";
    // print_width(w);
    // printf("\n");
    switch (w) {
    case U8:
        cpu.set_byte(address, value % 256);
        break;
    case U32:
        cpu.get_memory().set_quad(address, value);
        // cpu.set_byte(address, value & 0xff);
        // cpu.set_byte(address + 1, (value >> 8) & 0xff); // XXX resize mem if needed?
        // cpu.set_byte(address + 2, (value >> 16) & 0xff);
        // cpu.set_byte(address + 3, (value >> 24) & 0xff);
        break;
    }
}

void
MemoryLocation::print(Width w) {
    std::cout << "MemoryLocation: ";
    print_quad_in_hex(address);
    std::cout << " ";
}
