//
// Created by Joe Landers on 23.05.20.
//

#ifndef EXAMPLE_INSTRUCTIONFACTORY_H
#define EXAMPLE_INSTRUCTIONFACTORY_H

#include "InstructionBase.h"
#include "mylib.h"
#include "CPU.h"

class InstructionFactory {
  public:
    InstructionFactory();
    using InstructionConstructor = std::unique_ptr<InstructionBase>(*)(uint8_t, CPU& cpu);
    static bool register_opcodes(std::vector<uint8_t> opcodes, InstructionConstructor);
    static std::unique_ptr<InstructionBase> create(uint8_t opcode, CPU& cpu);

  private:
    static std::map<uint8_t, InstructionConstructor> instruction_set;
};


#endif // EXAMPLE_INSTRUCTIONFACTORY_H
