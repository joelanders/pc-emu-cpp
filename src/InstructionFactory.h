//
// Created by Joe Landers on 23.05.20.
//

#ifndef EXAMPLE_INSTRUCTIONFACTORY_H
#define EXAMPLE_INSTRUCTIONFACTORY_H

#include "mylib.h"
#include "InstructionBase.h"

class InstructionFactory {
  public:
    InstructionFactory();
    using InstructionConstructor = std::function<std::unique_ptr<InstructionBase>()>;
    static bool register_opcode(uint8_t opcode, InstructionConstructor);
    static std::unique_ptr<InstructionBase> create(uint8_t);

  private:
    static std::map<uint8_t, InstructionConstructor> instruction_set;
};




#endif // EXAMPLE_INSTRUCTIONFACTORY_H
