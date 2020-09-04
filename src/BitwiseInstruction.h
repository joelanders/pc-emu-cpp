#ifndef EXAMPLE_BITWISEINSTRUCTION_H
#define EXAMPLE_BITWISEINSTRUCTION_H

#include "CPU.h"
#include "InstructionBase.h"
#include "InstructionFactory.h"
#include "LocationBase.h"
#include "Operands.h"

class BitwiseInstruction : public InstructionBase {
  public:
    BitwiseInstruction(uint8_t opcode, CPU& cpu);
    virtual ~BitwiseInstruction(){};
    virtual bool execute(CPU& cpu);

    static std::unique_ptr<InstructionBase> create_method(uint8_t opcode, CPU& cpu) {
        return std::make_unique<BitwiseInstruction>(opcode, cpu);
    }

  private:
    uint8_t opcode;
    CPU& cpu;
    bool do_or(std::unique_ptr<LocationBase> dest, std::unique_ptr<LocationBase> src, Width w);
    static bool s_registered;
};

#endif // EXAMPLE_BITWISEINSTRUCTION_H
