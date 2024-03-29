//
// Created by Joe Landers on 23.05.20.
//

#ifndef EXAMPLE_INSTRUCTIONFACTORY_H
#define EXAMPLE_INSTRUCTIONFACTORY_H

#include "CPU.h"
#include "InstructionBase.h"
#include "util.h"

class InstructionFactory {
  public:
    InstructionFactory();
    using InstructionConstructor = std::unique_ptr<InstructionBase> (*)(uint8_t, CPU& cpu);
    static bool register_opcodes(std::vector<uint8_t> opcodes, InstructionConstructor);
    static std::unique_ptr<InstructionBase> create(uint8_t opcode, CPU& cpu);
    static void print_registered();

  private:
    static std::map<uint8_t, InstructionConstructor> instruction_set;
};


#endif // EXAMPLE_INSTRUCTIONFACTORY_H
