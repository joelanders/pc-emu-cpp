#include "BitwiseInstruction.h"
#include "util.h"

BitwiseInstruction::BitwiseInstruction(uint8_t opcode, CPU& cpu) : cpu(cpu), opcode(opcode){};

bool
BitwiseInstruction::execute(CPU& cpu) {
    std::cout << "BitwiseInstruction::execute " << std::endl;
    std::cout << "switching on opcode: ";
    print_byte_in_hex(opcode);
    printf("\n");
    switch (opcode) {
    case 0x08: {
        Width w = U8;
        auto operands = decode_modrm(cpu, w);
        operands.print(w);
        return do_or(std::move(operands.E()), std::move(operands.G()), w);
    }
    case 0x09: {
        Width w = U32;
        auto operands = decode_modrm(cpu, w);
        operands.print(w);
        return do_or(std::move(operands.E()), std::move(operands.G()), w);
    }
    case 0x0a: {
        Width w = U8;
        auto operands = decode_modrm(cpu, w);
        operands.print(w);
        return do_or(std::move(operands.G()), std::move(operands.E()), w);
    }
    case 0x0b: {
        Width w = U32;
        auto operands = decode_modrm(cpu, w);
        operands.print(w);
        return do_or(std::move(operands.G()), std::move(operands.E()), w);
    }
    case 0x0c: {
        Width w = U8;
        auto imm = std::make_unique<MemoryLocation>(cpu.get_registers().get_eip());
        cpu.get_registers().inc_eip();
        auto reg = std::make_unique<RegisterLocation>(index_to_register(Eax, w));
        imm->print(w);
        reg->print(w);
        return do_or(std::move(reg), std::move(imm), w);
    }
    case 0x0d: {
        Width w = U32;
        auto imm = std::make_unique<MemoryLocation>(cpu.get_registers().get_eip());
        cpu.get_registers().inc_eip();
        cpu.get_registers().inc_eip();
        cpu.get_registers().inc_eip();
        cpu.get_registers().inc_eip();
        auto reg = std::make_unique<RegisterLocation>(index_to_register(Eax, w));
        imm->print(w);
        reg->print(w);
        return do_or(std::move(reg), std::move(imm), w);
    }
    // XXX
    // XXX AND
    // XXX
    case 0x20: {
        Width w = U8;
        auto operands = decode_modrm(cpu, w);
        operands.print(w);
        return do_and(std::move(operands.E()), std::move(operands.G()), w);
    }
    case 0x21: {
        Width w = U32;
        auto operands = decode_modrm(cpu, w);
        operands.print(w);
        return do_and(std::move(operands.E()), std::move(operands.G()), w);
    }
    case 0x22: {
        Width w = U8;
        auto operands = decode_modrm(cpu, w);
        operands.print(w);
        return do_and(std::move(operands.G()), std::move(operands.E()), w);
    }
    case 0x23: {
        Width w = U32;
        auto operands = decode_modrm(cpu, w);
        operands.print(w);
        return do_and(std::move(operands.G()), std::move(operands.E()), w);
    }
    case 0x24: {
        Width w = U8;
        auto imm = std::make_unique<MemoryLocation>(cpu.get_registers().get_eip());
        cpu.get_registers().inc_eip();
        auto reg = std::make_unique<RegisterLocation>(index_to_register(Eax, w));
        imm->print(w);
        reg->print(w);
        return do_and(std::move(reg), std::move(imm), w);
    }
    case 0x25: {
        Width w = U32;
        auto imm = std::make_unique<MemoryLocation>(cpu.get_registers().get_eip());
        cpu.get_registers().inc_eip();
        cpu.get_registers().inc_eip();
        cpu.get_registers().inc_eip();
        cpu.get_registers().inc_eip();
        auto reg = std::make_unique<RegisterLocation>(index_to_register(Eax, w));
        imm->print(w);
        reg->print(w);
        return do_and(std::move(reg), std::move(imm), w);
    }
        // XXX
        // XXX XOR
        // XXX
    case 0x30: {
        Width w = U8;
        auto operands = decode_modrm(cpu, w);
        operands.print(w);
        return do_xor(std::move(operands.E()), std::move(operands.G()), w);
    }
    case 0x31: {
        Width w = U32;
        auto operands = decode_modrm(cpu, w);
        operands.print(w);
        return do_xor(std::move(operands.E()), std::move(operands.G()), w);
    }
    case 0x32: {
        Width w = U8;
        auto operands = decode_modrm(cpu, w);
        operands.print(w);
        return do_xor(std::move(operands.G()), std::move(operands.E()), w);
    }
    case 0x33: {
        Width w = U32;
        auto operands = decode_modrm(cpu, w);
        operands.print(w);
        return do_xor(std::move(operands.G()), std::move(operands.E()), w);
    }
    case 0x34: {
        Width w = U8;
        auto imm = std::make_unique<MemoryLocation>(cpu.get_registers().get_eip());
        cpu.get_registers().inc_eip();
        auto reg = std::make_unique<RegisterLocation>(index_to_register(Eax, w));
        imm->print(w);
        reg->print(w);
        return do_xor(std::move(reg), std::move(imm), w);
    }
    case 0x35: {
        Width w = U32;
        auto imm = std::make_unique<MemoryLocation>(cpu.get_registers().get_eip());
        cpu.get_registers().inc_eip();
        cpu.get_registers().inc_eip();
        cpu.get_registers().inc_eip();
        cpu.get_registers().inc_eip();
        auto reg = std::make_unique<RegisterLocation>(index_to_register(Eax, w));
        imm->print(w);
        reg->print(w);
        return do_xor(std::move(reg), std::move(imm), w);
    }
    }
    throw std::runtime_error("BitwiseInstruction execute() didn't find opcode");
}

bool
BitwiseInstruction::do_or(std::unique_ptr<LocationBase> dest, std::unique_ptr<LocationBase> src, Width w) {
    uint32_t a = dest->read(cpu, w);
    uint32_t b = src->read(cpu, w);
    uint32_t c = a | b;
    dest->write(cpu, w, c);
    cpu.get_registers().update_status_flags(a, b, c, w, false, true, true, false);
    return true;
}

bool
BitwiseInstruction::do_and(std::unique_ptr<LocationBase> dest, std::unique_ptr<LocationBase> src, Width w) {
    uint32_t a = dest->read(cpu, w);
    uint32_t b = src->read(cpu, w);
    uint32_t c = a & b;
    dest->write(cpu, w, c);
    cpu.get_registers().update_status_flags(a, b, c, w, false, true, true, false);
    return true;
}

bool
BitwiseInstruction::do_xor(std::unique_ptr<LocationBase> dest, std::unique_ptr<LocationBase> src, Width w) {
    uint32_t a = dest->read(cpu, w);
    uint32_t b = src->read(cpu, w);
    uint32_t c = a ^ b;
    dest->write(cpu, w, c);
    cpu.get_registers().update_status_flags(a, b, c, w, false, true, true, false);
    return true;
}

const std::vector<uint8_t> opcodes{0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d,
                                   0x20, 0x21, 0x22, 0x23, 0x24, 0x25,
                                   0x30, 0x31, 0x32, 0x33, 0x34, 0x35,
};

bool BitwiseInstruction::s_registered =
    InstructionFactory::register_opcodes(opcodes, BitwiseInstruction::create_method);
