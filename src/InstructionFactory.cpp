//
// Created by Joe Landers on 23.05.20.
//

#include "InstructionFactory.h"

InstructionFactory::InstructionFactory(){};
std::map<uint8_t, InstructionFactory::InstructionConstructor> InstructionFactory::instruction_set{};

bool
InstructionFactory::register_opcodes(std::vector<uint8_t> opcodes, InstructionConstructor constructor) {
    std::cout << "REGISTER OPCODES";
    for (auto const& opcode : opcodes) {
        std::cout << "SEARCHING for ";
        print_byte_in_hex(opcode);
        if (auto it = instruction_set.find(opcode); it == instruction_set.end()) {
            instruction_set[opcode] = constructor;
            std::cout << "REGISTERING" << std::endl;
        } else {
            std::cout << "BAD! DUPLICATE OPCODE" << std::endl;
        }
    }
    return true;
}

std::unique_ptr<InstructionBase>
InstructionFactory::create(uint8_t opcode, CPU& cpu) {
    std::cout << "create() looking for ";
    print_byte_in_hex(opcode);
    if (auto it = instruction_set.find(opcode); it != instruction_set.end()) {
        std::cout << "CREATING" << std::endl;
        return it->second(opcode, cpu);
    }
    // std::cout << "NOT CREATING" << std::endl;
    return nullptr;
}

void
InstructionFactory::print_registered() {
    for (auto i = 0; i < 0xff; i++) {
        if (auto it = instruction_set.find(i); it != instruction_set.end()) {
            print_byte_in_hex(i);
        } else {
            printf("   ");
        }
        if ((i+1) % 0x10 == 0) {
            printf("\n");
        }
    }
}