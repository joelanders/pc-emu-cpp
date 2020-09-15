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
    printf("\n");
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
    // XXX
    // XXX LOTS OF DUPLICATION
    // XXX
    case 0x10: {
        Width w = U8;
        auto operands = decode_modrm(cpu, w);
        operands.print(w);
        return add(std::move(operands.E()), std::move(operands.G()), w, true);
    }
    case 0x11: {
        Width w = U32;
        auto operands = decode_modrm(cpu, w);
        operands.print(w);
        return add(std::move(operands.E()), std::move(operands.G()), w, true);
    }
    case 0x12: {
        Width w = U8;
        auto operands = decode_modrm(cpu, w);
        operands.print(w);
        return add(std::move(operands.G()), std::move(operands.E()), w, true);
    }
    case 0x13: {
        Width w = U32;
        auto operands = decode_modrm(cpu, w);
        operands.print(w);
        return add(std::move(operands.G()), std::move(operands.E()), w, true);
    }
    case 0x14: {
        Width w = U8;
        auto imm = std::make_unique<MemoryLocation>(cpu.get_registers().get_eip());
        cpu.get_registers().inc_eip();
        auto reg = std::make_unique<RegisterLocation>(index_to_register(Eax, w));
        imm->print(w);
        reg->print(w);
        return add(std::move(reg), std::move(imm), w, true);
    }
    case 0x15: {
        Width w = U32;
        auto imm = std::make_unique<MemoryLocation>(cpu.get_registers().get_eip());
        cpu.get_registers().inc_eip();
        cpu.get_registers().inc_eip();
        cpu.get_registers().inc_eip();
        cpu.get_registers().inc_eip();
        auto reg = std::make_unique<RegisterLocation>(index_to_register(Eax, w));
        imm->print(w);
        reg->print(w);
        return add(std::move(reg), std::move(imm), w, true);
    }
    // XXX
    // XXX SBB
    // XXX
    case 0x18: {
        Width w = U8;
        auto operands = decode_modrm(cpu, w);
        operands.print(w);
        return sub(std::move(operands.E()), std::move(operands.G()), w, true);
    }
    case 0x19: {
        Width w = U32;
        auto operands = decode_modrm(cpu, w);
        operands.print(w);
        return sub(std::move(operands.E()), std::move(operands.G()), w, true);
    }
    case 0x1a: {
        Width w = U8;
        auto operands = decode_modrm(cpu, w);
        operands.print(w);
        return sub(std::move(operands.G()), std::move(operands.E()), w, true);
    }
    case 0x1b: {
        Width w = U32;
        auto operands = decode_modrm(cpu, w);
        operands.print(w);
        return sub(std::move(operands.G()), std::move(operands.E()), w, true);
    }
    case 0x1c: {
        Width w = U8;
        auto imm = std::make_unique<MemoryLocation>(cpu.get_registers().get_eip());
        cpu.get_registers().inc_eip();
        auto reg = std::make_unique<RegisterLocation>(index_to_register(Eax, w));
        imm->print(w);
        reg->print(w);
        return sub(std::move(reg), std::move(imm), w, true);
    }
    case 0x1d: {
        Width w = U32;
        auto imm = std::make_unique<MemoryLocation>(cpu.get_registers().get_eip());
        cpu.get_registers().inc_eip();
        cpu.get_registers().inc_eip();
        cpu.get_registers().inc_eip();
        cpu.get_registers().inc_eip();
        auto reg = std::make_unique<RegisterLocation>(index_to_register(Eax, w));
        imm->print(w);
        reg->print(w);
        return sub(std::move(reg), std::move(imm), w, true);
    }
        // XXX
        // XXX SUB
        // XXX
    case 0x28: {
        Width w = U8;
        auto operands = decode_modrm(cpu, w);
        operands.print(w);
        return sub(std::move(operands.E()), std::move(operands.G()), w);
    }
    case 0x29: {
        Width w = U32;
        auto operands = decode_modrm(cpu, w);
        operands.print(w);
        return sub(std::move(operands.E()), std::move(operands.G()), w);
    }
    case 0x2a: {
        Width w = U8;
        auto operands = decode_modrm(cpu, w);
        operands.print(w);
        return sub(std::move(operands.G()), std::move(operands.E()), w);
    }
    case 0x2b: {
        Width w = U32;
        auto operands = decode_modrm(cpu, w);
        operands.print(w);
        return sub(std::move(operands.G()), std::move(operands.E()), w);
    }
    case 0x2c: {
        Width w = U8;
        auto imm = std::make_unique<MemoryLocation>(cpu.get_registers().get_eip());
        cpu.get_registers().inc_eip();
        auto reg = std::make_unique<RegisterLocation>(index_to_register(Eax, w));
        imm->print(w);
        reg->print(w);
        return sub(std::move(reg), std::move(imm), w);
    }
    case 0x2d: {
        Width w = U32;
        auto imm = std::make_unique<MemoryLocation>(cpu.get_registers().get_eip());
        cpu.get_registers().inc_eip();
        cpu.get_registers().inc_eip();
        cpu.get_registers().inc_eip();
        cpu.get_registers().inc_eip();
        auto reg = std::make_unique<RegisterLocation>(index_to_register(Eax, w));
        imm->print(w);
        reg->print(w);
        return sub(std::move(reg), std::move(imm), w);
    }
        // XXX
        // XXX CMP
        // XXX
    case 0x38: {
        Width w = U8;
        auto operands = decode_modrm(cpu, w);
        operands.print(w);
        return cmp(std::move(operands.E()), std::move(operands.G()), w);
    }
    case 0x39: {
        Width w = U32;
        auto operands = decode_modrm(cpu, w);
        operands.print(w);
        return cmp(std::move(operands.E()), std::move(operands.G()), w);
    }
    case 0x3a: {
        Width w = U8;
        auto operands = decode_modrm(cpu, w);
        operands.print(w);
        return cmp(std::move(operands.G()), std::move(operands.E()), w);
    }
    case 0x3b: {
        Width w = U32;
        auto operands = decode_modrm(cpu, w);
        operands.print(w);
        return cmp(std::move(operands.G()), std::move(operands.E()), w);
    }
    case 0x3c: {
        Width w = U8;
        auto imm = std::make_unique<MemoryLocation>(cpu.get_registers().get_eip());
        cpu.get_registers().inc_eip();
        auto reg = std::make_unique<RegisterLocation>(index_to_register(Eax, w));
        imm->print(w);
        reg->print(w);
        return cmp(std::move(reg), std::move(imm), w);
    }
    case 0x3d: {
        Width w = U32;
        auto imm = std::make_unique<MemoryLocation>(cpu.get_registers().get_eip());
        cpu.get_registers().inc_eip();
        cpu.get_registers().inc_eip();
        cpu.get_registers().inc_eip();
        cpu.get_registers().inc_eip();
        auto reg = std::make_unique<RegisterLocation>(index_to_register(Eax, w));
        imm->print(w);
        reg->print(w);
        return cmp(std::move(reg), std::move(imm), w);
    }
    }
    throw std::runtime_error("ArithmeticInstruction failed to find opcode");
    return false;
}

//          Add,     Sub,     Cmp,     Adc,     Sbb
// r_imm,   04, 05,  2c, 2d,  3c, 3d,  14, 15,  1c, 1d
// rm_imm,
// rm_r,    00, 01,  28, 29,  38, 39,  10, 11,  18, 19
// r_rm,    02, 03,  2a, 2b,  3a, 3b,  12, 13,  1a, 1b

bool
ArithmeticInstruction::add(std::unique_ptr<LocationBase> dest, std::unique_ptr<LocationBase> src, Width w, bool carry) {
    uint32_t a = dest->read(cpu, w);
    uint32_t b = src->read(cpu, w);
    uint32_t c = a + b;
    if (carry) {
        if (cpu.get_registers().get_cf()) {
            c += 1;
        }
    }
    dest->write(cpu, w, c);
    cpu.get_registers().update_status_flags(a, b, c, w, false, false, false);
    return true;
}

bool
ArithmeticInstruction::sub(std::unique_ptr<LocationBase> dest, std::unique_ptr<LocationBase> src, Width w, bool borrow) {
    uint32_t a = dest->read(cpu, w);
    uint32_t b = src->read(cpu, w);
    uint32_t c = a - b;
    if (borrow) {
        if (cpu.get_registers().get_cf()) {
            c -= 1;
        }
    }
    dest->write(cpu, w, c);
    cpu.get_registers().update_status_flags(a, b, c, w, false, false, false);
    return true;
}

bool
ArithmeticInstruction::cmp(std::unique_ptr<LocationBase> dest, std::unique_ptr<LocationBase> src, Width w) {
    uint32_t a = dest->read(cpu, w);
    uint32_t b = src->read(cpu, w);
    uint32_t c = a - b;
    cpu.get_registers().update_status_flags(a, b, c, w, false, false, false);
    return true;
}

// XXX this isn't working in the tests
const std::vector<uint8_t> opcodes{0x00, 0x01, 0x02, 0x03, 0x04, 0x05,
                                   0x10, 0x11, 0x12, 0x13, 0x14, 0x15,
                                   0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d,
                                   0x28, 0x29, 0x2a, 0x2b, 0x2c, 0x2d,
                                   0x38, 0x39, 0x3a, 0x3b, 0x3c, 0x3d,
};

bool ArithmeticInstruction::s_registered =
    InstructionFactory::register_opcodes(opcodes, ArithmeticInstruction::create_method);
