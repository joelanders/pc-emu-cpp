//
// Created by Joe Landers on 23.05.20.
//

#include "InstructionFactory.h"

InstructionFactory::InstructionFactory(){};
std::map<uint8_t, InstructionFactory::InstructionConstructor> InstructionFactory::instruction_set{};

bool
InstructionFactory::register_opcode(uint8_t opcode, InstructionConstructor inst_const) {
    if (auto it = instruction_set.find(opcode); it == instruction_set.end()) {
        instruction_set[opcode] = inst_const;
        return true;
    }
    return false;
}

std::unique_ptr<InstructionBase>
InstructionFactory::create(uint8_t opcode) {
    if (auto it = instruction_set.find(opcode); it != instruction_set.end()) {
        std::cout << "CREATING" << std::endl;
        return it->second();
    }
    std::cout << "NOT CREATING" << std::endl;
    return nullptr;
}
