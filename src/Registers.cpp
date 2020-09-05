//
// Created by Joe Landers on 23.05.20.
//

#include "Registers.h"

Registers::Registers()
    : eax(0), ecx(0), edx(0), ebx(0), esp(0), ebp(0), esi(0), edi(0), eip(0), ss(0), cs(0), ds(0), es(0), fs(0), gs(0) {
}

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

    os << "\tss: ";
    os << std::setfill('0') << std::setw(8) << std::hex << registers.get_ss() << std::endl;
    os << "\tcs: ";
    os << std::setfill('0') << std::setw(8) << std::hex << registers.get_cs() << std::endl;
    os << "\tds: ";
    os << std::setfill('0') << std::setw(8) << std::hex << registers.get_ds() << std::endl;
    os << "\tes: ";
    os << std::setfill('0') << std::setw(8) << std::hex << registers.get_es() << std::endl;
    os << "\tfs: ";
    os << std::setfill('0') << std::setw(8) << std::hex << registers.get_fs() << std::endl;
    os << "\tgs: ";
    os << std::setfill('0') << std::setw(8) << std::hex << registers.get_gs() << std::endl;
    return os;
}

// XXX handle widths
bool
Registers::set_register(Width w, Register reg, uint32_t value) {
    uint32_t mask;
    switch (w) {
    case U8:
        mask = 0xff;
        break;
    case U16:
        mask = 0xffff;
        break;
    case U32:
        mask = 0xffffffff;
        break;
    }

    // XXX is this the right place to chomp the extra bits? make caller do it?
    std::cout << "REGSET offset: " << std::to_string(register_to_index(reg));
    std::cout << " value: ";
    print_quad_in_hex(value & mask);
    printf("\n");

    switch (reg) {
    case Eax:
        eax = (eax & ~mask) | (value & mask);
        break;
    case Ecx:
        ecx = (ecx & ~mask) | (value & mask);
        break;
    case Edx:
        edx = (edx & ~mask) | (value & mask);
        break;
    case Ebx:
        ebx = (ebx & ~mask) | (value & mask);
        break;
    case Esp:
        esp = (esp & ~mask) | (value & mask);
        break;
    case Ebp:
        ebp = (ebp & ~mask) | (value & mask);
        break;
    case Esi:
        esi = (esi & ~mask) | (value & mask);
        break;
    case Edi:
        edi = (edi & ~mask) | (value & mask);
        break;
    case Eip:
        eip = (eip & ~mask) | (value & mask);
        break;
    case Ss:
        ss = (ss & ~mask) | (value & mask);
        break;
    case Cs:
        cs = (cs & ~mask) | (value & mask);
        break;
    case Ds:
        ds = (ds & ~mask) | (value & mask);
        break;
    case Es:
        es = (es & ~mask) | (value & mask);
        break;
    case Fs:
        fs = (fs & ~mask) | (value & mask);
        break;
    case Gs:
        gs = (gs & ~mask) | (value & mask);
        break;
    }
    return true;
}

uint32_t
Registers::get_register_by_index(size_t index, Width w) {
    uint32_t mask;
    switch (w) {
    case U8:
        mask = 0xff;
        break;
    case U16:
        mask = 0xffff;
        break;
    case U32:
        mask = 0xffffffff;
        break;
    }

    switch (index) {
    case 0b000:
        return eax & mask;
    case 0b001:
        return ecx & mask;
    case 0b010:
        return edx & mask;
    case 0b011:
        return ebx & mask;
    case 0b100:
        return esp & mask;
    case 0b101:
        return ebp & mask;
    case 0b110:
        return esi & mask;
    case 0b111:
        return edi & mask;
    }
}
