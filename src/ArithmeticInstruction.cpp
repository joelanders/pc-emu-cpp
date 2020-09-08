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
        Width w = U8;
        auto operands = decode_modrm(cpu, w);
        operands.print(w);
        return add(std::move(operands.E()), std::move(operands.G()), w);
    }
    case 0x01: {
        Width w = U32;
        auto operands = decode_modrm(cpu, w);
        operands.print(w);
        return add(std::move(operands.E()), std::move(operands.G()), w);
    }
    case 0x02: {
        Width w = U8;
        auto operands = decode_modrm(cpu, w);
        operands.print(w);
        return add(std::move(operands.G()), std::move(operands.E()), w);
    }
    case 0x03: {
        Width w = U32;
        auto operands = decode_modrm(cpu, w);
        operands.print(w);
        return add(std::move(operands.G()), std::move(operands.E()), w);
    }
    case 0x04: {
        Width w = U8;
        auto imm = std::make_unique<MemoryLocation>(cpu.get_registers().get_eip());
        cpu.get_registers().inc_eip();
        auto reg = std::make_unique<RegisterLocation>(index_to_register(Eax, w));
        imm->print(w);
        reg->print(w);
        return add(std::move(reg), std::move(imm), w);
    }
    case 0x05: {
        Width w = U32;
        auto imm = std::make_unique<MemoryLocation>(cpu.get_registers().get_eip());
        cpu.get_registers().inc_eip();
        cpu.get_registers().inc_eip();
        cpu.get_registers().inc_eip();
        cpu.get_registers().inc_eip();
        auto reg = std::make_unique<RegisterLocation>(index_to_register(Eax, w));
        imm->print(w);
        reg->print(w);
        return add(std::move(reg), std::move(imm), w);
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
ArithmeticInstruction::add(std::unique_ptr<LocationBase> dest, std::unique_ptr<LocationBase> src, Width w) {
    uint32_t a = dest->read(cpu, w);
    uint32_t b = src->read(cpu, w);
    uint32_t c = a + b;
    dest->write(cpu, w, c);
    cpu.get_registers().update_status_flags(a, b, c, w, false, false, false);
    return true;
}

// XXX this isn't working in the tests
const std::vector<uint8_t> opcodes{0x00, 0x01, 0x02, 0x03, 0x04, 0x05};

bool ArithmeticInstruction::s_registered =
    InstructionFactory::register_opcodes(opcodes, ArithmeticInstruction::create_method);
