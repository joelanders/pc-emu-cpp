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
        auto src = MemoryLocation(0x00);
        auto dest = MemoryLocation(0x01);
        return add(src, dest);
    }
    case 0x01: {
        std::cout << "FUCK 111" << std::endl;
        auto src = MemoryLocation(0x00);
        auto dest = RegisterLocation(Eax);
        return add(src, dest); // XXX dummy locations
    }
    }
    return false;
}

bool
ArithmeticInstruction::add(LocationBase& dest, LocationBase& src) {
    dest.write(cpu, U8, dest.read(cpu, U8) + src.read(cpu, U8));
    return true;
}
