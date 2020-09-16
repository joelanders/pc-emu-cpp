#include "Operands.h"

// XXX initializer list...
Operands::Operands(std::unique_ptr<LocationBase> E, std::unique_ptr<RegisterLocation> G) {
    e = std::move(E);
    g = std::move(G);
}

std::unique_ptr<LocationBase>
Operands::E() {
    return std::move(e);
}

std::unique_ptr<RegisterLocation>
Operands::G() {
    return std::move(g);
}

void
Operands::print(Width w) {
    std::cout << "E: ";
    e->print(w);
    printf("\n");
    std::cout << "G: ";
    g->print(w);  // XXX register should know its width
    printf("\n");
}


// mod: 00: rm specifies a memory address stored in a register
// mod: 11: rm specifies a register
Operands
decode_modrm(CPU& cpu, Width w) {
    uint8_t modrm = cpu.get_memory().get_byte(cpu.get_registers().get_eip(), true);
    cpu.get_registers().inc_eip();
    std::cout << "MOD / REG / RM: " << std::bitset<8>(modrm) << std::endl;

    uint8_t mod = (modrm & 0b11000000) >> 6;
    uint8_t reg = (modrm & 0b00111000) >> 3;
    uint8_t rm = (modrm & 0b00000111);

    if (mod == 0b11) {
        std::cout << "-- register-to-register mode --" << std::endl;
        auto operands = Operands(std::make_unique<RegisterLocation>(index_to_register(rm, w)),
                                 std::make_unique<RegisterLocation>(index_to_register(reg, w)));
        return operands;
    }

    // no SIB byte
    if (rm != 0b100) {
        if (mod == 0b01) {
            uint32_t address = cpu.get_registers().get_register_by_index(rm, U32);
            int8_t disp8 = cpu.get_memory().get_byte(cpu.get_registers().get_eip(), true);
            // XXX am i doing this right?
            if (disp8 > 127) {
                disp8 -= 256;  // XXX 256 is larger than an int8 holds
            }
            cpu.get_registers().inc_eip();
            return Operands(std::make_unique<MemoryLocation>(address + disp8),
                            std::make_unique<RegisterLocation>(index_to_register(reg, w)));
        }
        if (mod == 0b10) {
            uint32_t address = cpu.get_registers().get_register_by_index(rm, U32);
            int32_t disp32 = cpu.get_memory().get_quad(cpu.get_registers().get_eip());
            // XXX am i doing this right?
            cpu.get_registers().inc_eip();
            cpu.get_registers().inc_eip();
            cpu.get_registers().inc_eip();
            cpu.get_registers().inc_eip();
            return Operands(std::make_unique<MemoryLocation>(address + disp32),
                            std::make_unique<RegisterLocation>(index_to_register(reg, w)));
        }
        // at this point, mod == 0b00
        if (rm != 0b101) {
            uint32_t address = cpu.get_registers().get_register_by_index(rm, U32);
            return Operands(std::make_unique<MemoryLocation>(address),
                            std::make_unique<RegisterLocation>(index_to_register(reg, w)));
        } else {
            // XXX is this right?
            uint32_t disp32 = cpu.get_memory().get_quad(cpu.get_registers().get_eip());
            cpu.get_registers().inc_eip();
            cpu.get_registers().inc_eip();
            cpu.get_registers().inc_eip();
            cpu.get_registers().inc_eip();
            return Operands(std::make_unique<MemoryLocation>(disp32),
                            std::make_unique<RegisterLocation>(index_to_register(reg, w)));
        }
    }
    // at this point, there is a SIB byte
    uint8_t sib = cpu.get_memory().get_byte(cpu.get_registers().get_eip(), true);
    cpu.get_registers().inc_eip();

    uint8_t scale = (sib & 0b11000000) >> 6;
    uint8_t index = (sib & 0b00111000) >> 3;
    uint8_t base = (sib & 0b00000111);

    // XXX double check this two's complement stuff
    uint32_t disp = 0;
    int32_t signed_disp = 0;
    if (mod == 0b00) {
        disp = 0;
        signed_disp = 0;
    } else if (mod == 0b01) {
        disp = cpu.get_memory().get_byte(cpu.get_registers().get_eip(), true);
        if (disp > (1 << 7) - 1) {
            signed_disp = disp - (int32_t)0xff - 1;
        } else {
            signed_disp = disp;
        }
    } else /* if (mod == 0b10) */ {
        disp = cpu.get_memory().get_quad(cpu.get_registers().get_eip());
        if (disp > (1 << 15) - 1) {
            signed_disp = disp - (int32_t)0xffffffff - 1;
        } else {
            signed_disp = disp;
        }
        cpu.get_registers().inc_eip();
        cpu.get_registers().inc_eip();
        cpu.get_registers().inc_eip();
        cpu.get_registers().inc_eip();
    }
    printf("XXX unsigned_disp: %u\n", disp);
    printf("XXX signed_disp: %d\n", signed_disp);

    uint32_t scaled_index = 0;
    if (index == 0b100) {
        scaled_index = 0;
    } else {
        scaled_index = cpu.get_registers().get_register_by_index(index, U32) << scale;
    }

    uint32_t base_value = 0;
    if (base == 0b101 && mod == 0b00) {
        base_value = cpu.get_memory().get_quad(cpu.get_registers().get_eip());
        cpu.get_registers().inc_eip();
        cpu.get_registers().inc_eip();
        cpu.get_registers().inc_eip();
        cpu.get_registers().inc_eip();
    } else {
        base_value = cpu.get_registers().get_register_by_index(base, U32);
    }

    return Operands(std::make_unique<MemoryLocation>(signed_disp + scaled_index + base_value),
                    std::make_unique<RegisterLocation>(index_to_register(reg, w)));
}
