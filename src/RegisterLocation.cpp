//
// Created by Joe Landers on 23.05.20.
//

#include "RegisterLocation.h"

RegisterLocation::RegisterLocation(Register reg) { reg = reg; }

uint32_t
RegisterLocation::read(CPU& cpu, Width w) {
    uint32_t value;
    switch (reg) {
    case Eax:
        value = cpu.get_registers().get_eax();
        break;
    case Ecx:
        value = cpu.get_registers().get_ecx();
        break;
    }

    std::cout << "RegisterLocation::read() from reg ";
    print_register(reg);
    std::cout << " value ";
    print_quad_in_hex(value);
    std::cout << " width ";
    print_width(w);
    printf("\n");
    return value;
}

bool
RegisterLocation::write(CPU& cpu, Width w, uint32_t value) {
    std::cout << "RegisterLocation::write() to reg ";
    print_register(reg);
    std::cout << " value ";
    print_quad_in_hex(value);
    std::cout << " width ";
    print_width(w);
    printf("\n");

    return cpu.set_register(w, reg, value);
}

void
RegisterLocation::print() {
    std::cout << "RegisterLocation: ";
    print_register(reg);
    std::cout << " ";
}
