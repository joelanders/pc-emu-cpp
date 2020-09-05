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
Operands::print() {
    std::cout << "E: ";
    e->print(U32);
    printf("\n");
    std::cout << "G: ";
    g->print(U32);  // XXX register should know its width
    printf("\n");
}


// mod: 00: rm specifies a memory address stored in a register
// mod: 11: rm specifies a register
Operands
decode_modrm(CPU& cpu) {
    uint8_t modrm = cpu.get_memory().get_byte(cpu.get_registers().get_eip());
    cpu.get_registers().inc_eip();
    std::cout << "MOD / REG / RM: " << std::bitset<8>(modrm) << std::endl;

    uint8_t mod = (modrm & 0b11000000) >> 6;
    uint8_t reg = (modrm & 0b00111000) >> 3;
    uint8_t rm = (modrm & 0b00000111);

    if (mod == 0b11) {
        std::cout << "-- register-to-register mode --" << std::endl;
        auto operands = Operands(std::make_unique<RegisterLocation>(index_to_register(rm)),
                                 std::make_unique<RegisterLocation>(index_to_register(reg)));
        return operands;
    }

    // no SIB byte
    if (rm != 0b100) {
        if (mod == 0b01) {
            uint32_t address = cpu.get_registers().get_register_by_index(rm, U32);
            uint8_t disp8 = cpu.get_memory().get_byte(cpu.get_registers().get_eip());
            cpu.get_registers().inc_eip();
            return Operands(std::make_unique<MemoryLocation>(address + disp8),
                            std::make_unique<RegisterLocation>(index_to_register(reg)));
        }
        if (mod == 0b10) {
            uint32_t address = cpu.get_registers().get_register_by_index(rm, U32);
            uint32_t disp32 = cpu.get_memory().get_quad(cpu.get_registers().get_eip());
            cpu.get_registers().inc_eip();
            cpu.get_registers().inc_eip();
            cpu.get_registers().inc_eip();
            cpu.get_registers().inc_eip();
            return Operands(std::make_unique<MemoryLocation>(address + disp32),
                            std::make_unique<RegisterLocation>(index_to_register(reg)));
        }
        // at this point, mod == 0b00
        if (rm != 0b101) {
            uint32_t address = cpu.get_registers().get_register_by_index(rm, U32);
            return Operands(std::make_unique<MemoryLocation>(address),
                            std::make_unique<RegisterLocation>(index_to_register(reg)));
        } else {
            uint32_t disp32 = cpu.get_memory().get_quad(cpu.get_registers().get_eip());
            cpu.get_registers().inc_eip();
            cpu.get_registers().inc_eip();
            cpu.get_registers().inc_eip();
            cpu.get_registers().inc_eip();
            return Operands(std::make_unique<MemoryLocation>(disp32),
                            std::make_unique<RegisterLocation>(index_to_register(reg)));
        }
    }
    // at this point, there is a SIB byte
    uint8_t sib = cpu.get_memory().get_byte(cpu.get_registers().get_eip());
    cpu.get_registers().inc_eip();

    uint8_t scale = (sib & 0b11000000) >> 6;
    uint8_t index = (sib & 0b00111000) >> 3;
    uint8_t base = (sib & 0b00000111);

    uint32_t disp = 0;
    if (mod == 0b00) {
        disp = 0;
    } else if (mod == 0b01) {
        disp = cpu.get_memory().get_byte(cpu.get_registers().get_eip());
        cpu.get_registers().inc_eip();
    } else /* if (mod == 0b10) */ {
        disp = cpu.get_memory().get_quad(cpu.get_registers().get_eip());
        cpu.get_registers().inc_eip();
        cpu.get_registers().inc_eip();
        cpu.get_registers().inc_eip();
        cpu.get_registers().inc_eip();
    }

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

    return Operands(std::make_unique<MemoryLocation>(disp + scaled_index + base_value),
                    std::make_unique<RegisterLocation>(index_to_register(reg)));
}
