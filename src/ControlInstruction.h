//
// Created by Joe Landers on 28.12.20.
//

#ifndef EXAMPLE_CONTROLINSTRUCTION_H
#define EXAMPLE_CONTROLINSTRUCTION_H


#include "CPU.h"
#include "InstructionBase.h"

class ControlInstruction : public InstructionBase {
  public:
    ControlInstruction(uint8_t opcode, CPU& cpu);
    virtual ~ControlInstruction(){};
    virtual bool execute(CPU& cpu);

    static std::unique_ptr<InstructionBase> create_method(uint8_t opcode, CPU& cpu) {
        return std::make_unique<ControlInstruction>(opcode, cpu);
    }

  private:
    uint8_t opcode;
    CPU& cpu;
    static bool s_registered;
};


#endif // EXAMPLE_CONTROLINSTRUCTION_H
