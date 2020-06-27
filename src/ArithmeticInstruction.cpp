//
// Created by Joe Landers on 23.05.20.
//

#include "ArithmeticInstruction.h"
#include <bitset>

ArithmeticInstruction::ArithmeticInstruction(uint8_t opcode, CPU& cpu) : cpu(cpu), opcode(opcode){};

bool
ArithmeticInstruction::execute(CPU& cpu) {
    std::cout << "ArithmeticInstruction::execute " << std::endl;
    std::cout << "switching on opcode: ";
    print_byte_in_hex(opcode);
    switch (opcode) {
    case 0x00: {
        std::cout << "opcode 0x00" << std::endl;
        Width w = U8;
        auto rm_reg = decode_modrm(cpu);
        auto dest = std::move(rm_reg.first);
        auto src = std::move(rm_reg.second);
        std::cout << "dest: ";
        dest->print();
        printf("\n");
        std::cout << "src: ";
        src->print();
        printf("\n");
        return add(std::move(dest), std::move(src), w);
    }
    case 0x01: {
        std::cout << "opcode 0x01" << std::endl;
        Width w = U32;
        auto rm_reg = decode_modrm(cpu);
        auto dest = std::move(rm_reg.first);
        auto src = std::move(rm_reg.second);
        std::cout << "dest: ";
        dest->print();
        printf("\n");
        std::cout << "src: ";
        src->print();
        printf("\n");
        return add(std::move(dest), std::move(src), w);
    }
    case 0x02: {
        std::cout << "opcode 0x02" << std::endl;
        Width w = U8;
        auto rm_reg = decode_modrm(cpu);
        auto dest = std::move(rm_reg.second);
        auto src = std::move(rm_reg.first);
        std::cout << "dest: ";
        dest->print();
        printf("\n");
        std::cout << "src: ";
        src->print();
        printf("\n");
        return add(std::move(dest), std::move(src), w);
    }
    case 0x03: {
        std::cout << "opcode 0x03" << std::endl;
        Width w = U32;
        auto rm_reg = decode_modrm(cpu);
        auto dest = std::move(rm_reg.second);
        auto src = std::move(rm_reg.first);
        std::cout << "dest: ";
        dest->print();
        printf("\n");
        std::cout << "src: ";
        src->print();
        printf("\n");
        return add(std::move(dest), std::move(src), w);
    }
    }
    return false;
}

//          Add,     Sub,     Cmp,     Adc,     Sbb
// r_imm,   04, 05,  2c, 2d,  3c, 3d,  14, 15,  1c, 1d
// rm_imm,
// rm_r,    00, 01,  28, 29,  38, 39,  10, 11,  18, 19
// r_rm,    02, 03,  2a, 2b,  3a, 3b,  12, 13,  1a, 1b

bool
ArithmeticInstruction::add(std::unique_ptr<LocationBase> dest,
                           std::unique_ptr<LocationBase> src,
                           Width w) {
    dest->write(cpu, w, dest->read(cpu, w) + src->read(cpu, w));
    return true;
}

const std::vector<uint8_t> opcodes { 0x00, 0x01, 0x02, 0x03 };

bool
ArithmeticInstruction::s_registered =
    InstructionFactory::register_opcodes(opcodes,
                                         ArithmeticInstruction::create_method);

// mod: 00: rm specifies a memory address stored in a register
// mod: 11: rm specifies a register
std::pair<std::unique_ptr<LocationBase>, std::unique_ptr<RegisterLocation>>
decode_modrm(CPU& cpu) {
    uint8_t modrm = cpu.get_memory().get_byte(cpu.get_registers().get_eip());
    cpu.get_registers().inc_eip();
    std::cout << "MOD / REG / RM: " << std::bitset<8>(modrm)  << std::endl;

    uint8_t mod = (modrm & 0b11000000) >> 6;
    uint8_t reg = (modrm & 0b00111000) >> 3;
    uint8_t rm  = (modrm & 0b00000111);

    if (mod == 0b11) {
        return std::make_pair(std::make_unique<RegisterLocation>(index_to_register(rm)),
                              std::make_unique<RegisterLocation>(index_to_register(reg))
        );
    }

    // no SIB byte
    if (rm != 0b100) {
        if (mod == 0b01) {
            uint32_t address = cpu.get_registers().get_register_by_index(rm, U32);
            uint8_t disp8 = cpu.get_memory().get_byte(cpu.get_registers().get_eip());
            cpu.get_registers().inc_eip();
            return std::make_pair(std::make_unique<MemoryLocation>(address + disp8),
                                  std::make_unique<RegisterLocation>(index_to_register(reg)));
        }
        if (mod == 0b10) {
            uint32_t address = cpu.get_registers().get_register_by_index(rm, U32);
            uint32_t disp32 = cpu.get_memory().get_quad(cpu.get_registers().get_eip());
            cpu.get_registers().inc_eip();
            cpu.get_registers().inc_eip();
            cpu.get_registers().inc_eip();
            cpu.get_registers().inc_eip();
            return std::make_pair(std::make_unique<MemoryLocation>(address + disp32),
                                  std::make_unique<RegisterLocation>(index_to_register(reg)));
        }
        // at this point, mod == 0b00
        if (rm != 0b101) {
            uint32_t address = cpu.get_registers().get_register_by_index(rm, U32);
            return std::make_pair(std::make_unique<MemoryLocation>(address),
                                  std::make_unique<RegisterLocation>(index_to_register(reg)));
        } else {
            uint32_t disp32 = cpu.get_memory().get_quad(cpu.get_registers().get_eip());
            cpu.get_registers().inc_eip();
            cpu.get_registers().inc_eip();
            cpu.get_registers().inc_eip();
            cpu.get_registers().inc_eip();
            return std::make_pair(std::make_unique<MemoryLocation>(disp32),
                                  std::make_unique<RegisterLocation>(index_to_register(reg)));
        }
    }
    // at this point, there is a SIB byte
    uint8_t sib = cpu.get_memory().get_byte(cpu.get_registers().get_eip());
    cpu.get_registers().inc_eip();

    uint8_t scale = (sib & 0b11000000) >> 6;
    uint8_t index = (sib & 0b00111000) >> 3;
    uint8_t base  = (sib & 0b00000111);

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

    return std::make_pair(std::make_unique<MemoryLocation>(disp + scaled_index + base_value),
                            std::make_unique<RegisterLocation>(index_to_register(reg)));
}
