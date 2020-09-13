//
// Created by Joe Landers on 23.05.20.
//

#ifndef EXAMPLE_ARITHMETICINSTRUCTION_H
#define EXAMPLE_ARITHMETICINSTRUCTION_H

#include "InstructionBase.h"
#include "InstructionFactory.h"
#include "LocationBase.h"
#include "MemoryLocation.h"
#include "Operands.h"
#include "RegisterLocation.h"
#include "util.h"

class ArithmeticInstruction : public InstructionBase {
  public:
    ArithmeticInstruction(uint8_t opcode, CPU& cpu);
    virtual ~ArithmeticInstruction(){};
    virtual bool execute(CPU& cpu);

    static std::unique_ptr<InstructionBase> create_method(uint8_t opcode, CPU& cpu) {
        return std::make_unique<ArithmeticInstruction>(opcode, cpu);
    }

  private:
    uint8_t opcode;
    CPU& cpu;
    bool add(std::unique_ptr<LocationBase> dest, std::unique_ptr<LocationBase> src, Width w, bool carry=false);
    bool sub(std::unique_ptr<LocationBase> dest, std::unique_ptr<LocationBase> src, Width w, bool borrow=false);
    bool cmp(std::unique_ptr<LocationBase> dest, std::unique_ptr<LocationBase> src, Width w);

    // constexpr static const std::vector<uint8_t> opcodes;
    static bool s_registered;
};


#endif // EXAMPLE_ARITHMETICINSTRUCTION_H
