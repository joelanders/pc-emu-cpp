//
// Created by Joe Landers on 23.05.20.
//

#include "RegisterLocation.h"

RegisterLocation::RegisterLocation(Register reg) { reg = reg; }

uint32_t
RegisterLocation::read(CPU& cpu, Width w) {
    switch (reg) {
        case Eax:
            return cpu.get_registers().get_eax();
            break;
        case Ecx:
            return cpu.get_registers().get_ecx();
            break;
    }
}

uint32_t
RegisterLocation::write(CPU& cpu, Width w, uint32_t value) {
    return 0x69;
}

