//
// Created by Joe Landers on 23.05.20.
//

#include "ArithmeticInstruction.h"

ArithmeticInstruction::ArithmeticInstruction(uint8_t opcode, CPU& cpu) : cpu(cpu), opcode(opcode){};

bool
ArithmeticInstruction::execute() {
    std::cout << "SHIIIIIT 000" << std::endl;
    std::cout << "switching on opcode: ";
    print_byte_in_hex(opcode);
    switch (opcode) {
    case 0x00: {
        std::cout << "FUCK 000" << std::endl;
        auto dest = MemoryLocation(0x00);
        auto src = MemoryLocation(0x01);
        return add(dest, src);
    }
    case 0x01: {
        std::cout << "FUCK 111" << std::endl;
        auto src = MemoryLocation(0x00);
        auto dest = RegisterLocation(Eax);
        return add(dest, src); // XXX dummy locations
    }
    }
    return false;
}

bool
ArithmeticInstruction::add(LocationBase& dest, LocationBase& src) {
    dest.write(cpu, U8, dest.read(cpu, U8) + src.read(cpu, U8));
    return true;
}

const std::vector<uint8_t> opcodes { 0x00, 0x01 };

bool
ArithmeticInstruction::s_registered =
    InstructionFactory::register_opcodes(opcodes,
                                         ArithmeticInstruction::create_method);
