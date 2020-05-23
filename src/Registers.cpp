//
// Created by Joe Landers on 23.05.20.
//

#include "Registers.h"

Registers::Registers() : eip(0) {}

std::ostream&
operator<<(std::ostream& os, const Registers& registers) {
    os << "Registers:" << std::endl;
    os << "\teax: ";
    os << std::setfill('0') << std::setw(8) << std::hex << registers.get_eax() << std::endl;
    os << "\tecx: ";
    os << std::setfill('0') << std::setw(8) << std::hex << registers.get_ecx() << std::endl;
    os << "\tebx: ";
    os << std::setfill('0') << std::setw(8) << std::hex << registers.get_ebx() << std::endl;
    os << "\tedx: ";
    os << std::setfill('0') << std::setw(8) << std::hex << registers.get_edx() << std::endl;
    os << "\teip: ";
    os << std::setfill('0') << std::setw(8) << std::hex << registers.get_eip() << std::endl;
    return os;
}

// XXX handle widths
bool
Registers::set_register(Width w, Register reg, uint32_t value) {
    std::cout << "Registers::set_register() to reg " << reg;
    std::cout << " value ";
    print_quad_in_hex(value);
    printf("\n");

    switch (reg) {
    case Eax:
        eax = value;
        break;
    case Ecx:
        ecx = value;
        break;
    case Ebx:
        ebx = value;
        break;
    case Edx:
        edx = value;
        break;
    }
    return true;
}
