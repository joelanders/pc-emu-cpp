//
// Created by Joe Landers on 23.05.20.
//

#include "RegisterLocation.h"

RegisterLocation::RegisterLocation(Register new_reg) {
    std::cout << "RegisterLocation::RegisterLocation(): ";
    // print_register(new_reg, U8);
    printf("\n");
    reg = new_reg;
}

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
    case Edx:
        value = cpu.get_registers().get_edx();
        break;
    case Ebx:
        value = cpu.get_registers().get_ebx();
        break;
    case Esp:
        value = cpu.get_registers().get_esp();
        break;
    case Ebp:
        value = cpu.get_registers().get_ebp();
        break;
    case Esi:
        value = cpu.get_registers().get_esi();
        break;
    case Edi:
        value = cpu.get_registers().get_edi();
        break;
    }

    std::cout << "RegisterLocation::read() from reg ";
    print_register(reg, w);
    std::cout << " value ";
    print_quad_in_hex(value);
    std::cout << " width ";
    print_width(wid);
    printf("\n");
    return value;
}

void
RegisterLocation::write(CPU& cpu, Width w, uint32_t value) {
    std::cout << "RegisterLocation::write() to reg ";
    print_register(reg, w);
    std::cout << " value ";
    print_quad_in_hex(value);
    std::cout << " width ";
    print_width(wid);
    printf("\n");

    return cpu.set_register(w, reg, value);
}

void
RegisterLocation::print(Width w) {
    std::cout << "RegisterLocation: ";
    print_register(reg, w);
    std::cout << " ";
}
