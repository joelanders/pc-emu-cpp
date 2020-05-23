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

