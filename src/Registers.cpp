//
// Created by Joe Landers on 23.05.20.
//

#include "Registers.h"

Registers::Registers() :
     eax(0),
     ecx(0),
     edx(0),
     ebx(0),
     esp(0),
     ebp(0),
     esi(0),
     edi(0),
     eip(0)
{}

std::ostream&
operator<<(std::ostream& os, const Registers& registers) {
    os << "Registers:" << std::endl;
    os << "\teax: ";
    os << std::setfill('0') << std::setw(8) << std::hex << registers.get_eax() << std::endl;
    os << "\tecx: ";
    os << std::setfill('0') << std::setw(8) << std::hex << registers.get_ecx() << std::endl;
    os << "\tedx: ";
    os << std::setfill('0') << std::setw(8) << std::hex << registers.get_edx() << std::endl;
    os << "\tebx: ";
    os << std::setfill('0') << std::setw(8) << std::hex << registers.get_ebx() << std::endl;

    os << "\tesp: ";
    os << std::setfill('0') << std::setw(8) << std::hex << registers.get_esp() << std::endl;
    os << "\tebp: ";
    os << std::setfill('0') << std::setw(8) << std::hex << registers.get_ebp() << std::endl;
    os << "\tesi: ";
    os << std::setfill('0') << std::setw(8) << std::hex << registers.get_esi() << std::endl;
    os << "\tedi: ";
    os << std::setfill('0') << std::setw(8) << std::hex << registers.get_edi() << std::endl;

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
    case Edx:
        edx = value;
        break;
    case Ebx:
        ebx = value;
        break;
    case Esp:
        esp = value;
        break;
    case Ebp:
        ebp = value;
        break;
    case Esi:
        esi = value;
        break;
    case Edi:
        edi = value;
        break;
    }
    return true;
}

uint32_t
Registers::get_register_by_index(size_t index, Width w) {
    switch (index) {
        case 0b000:
            return eax;
        case 0b001:
            return ecx;
        case 0b010:
            return edx;
        case 0b011:
            return ebx;
        case 0b100:
            return esp;
        case 0b101:
            return ebp;
        case 0b110:
            return esi;
        case 0b111:
            return edi;
    }
}
