#include "BitwiseInstruction.h"
#include "util.h"

BitwiseInstruction::BitwiseInstruction(uint8_t opcode, CPU& cpu) : cpu(cpu), opcode(opcode){};

bool
BitwiseInstruction::execute(CPU& cpu) {
    std::cout << "BitwiseInstruction::execute " << std::endl;
    std::cout << "switching on opcode: ";
    print_byte_in_hex(opcode);
    switch (opcode) {
    case 0x08: {
        Width w = U8;
        auto operands = decode_modrm(cpu);
        operands.print();
        return do_or(std::move(operands.E()), std::move(operands.G()), w);
    }
    case 0x09: {
        Width w = U32;
        auto operands = decode_modrm(cpu);
        operands.print();
        return do_or(std::move(operands.E()), std::move(operands.G()), w);
    }
    case 0x0a: {
        Width w = U8;
        auto operands = decode_modrm(cpu);
        operands.print();
        return do_or(std::move(operands.G()), std::move(operands.E()), w);
    }
    case 0x0b: {
        Width w = U32;
        auto operands = decode_modrm(cpu);
        operands.print();
        return do_or(std::move(operands.G()), std::move(operands.E()), w);
    }
    case 0x0c: {
        Width w = U8;
        auto imm = std::make_unique<MemoryLocation>(cpu.get_registers().get_eip());
        cpu.get_registers().inc_eip();
        auto reg = std::make_unique<RegisterLocation>(index_to_register(Eax));
        imm->print();
        reg->print();
        return do_or(std::move(reg), std::move(imm), w);
    }
    case 0x0d: {
        Width w = U32;
        auto imm = std::make_unique<MemoryLocation>(cpu.get_registers().get_eip());
        cpu.get_registers().inc_eip();
        cpu.get_registers().inc_eip();
        cpu.get_registers().inc_eip();
        cpu.get_registers().inc_eip();
        auto reg = std::make_unique<RegisterLocation>(index_to_register(Eax));
        imm->print();
        reg->print();
        return do_or(std::move(reg), std::move(imm), w);
    }
    }
}

bool
BitwiseInstruction::do_or(std::unique_ptr<LocationBase> dest,
                          std::unique_ptr<LocationBase> src,
                          Width w) {
    dest->write(cpu, w, dest->read(cpu, w) | src->read(cpu, w));
    return true;
}

const std::vector<uint8_t> opcodes { 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d };

bool
BitwiseInstruction::s_registered =
    InstructionFactory::register_opcodes(opcodes,
                                         BitwiseInstruction::create_method);

