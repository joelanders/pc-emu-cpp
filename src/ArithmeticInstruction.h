//
// Created by Joe Landers on 23.05.20.
//

#ifndef EXAMPLE_ARITHMETICINSTRUCTION_H
#define EXAMPLE_ARITHMETICINSTRUCTION_H

#include "InstructionBase.h"
#include "InstructionFactory.h"
#include "LocationBase.h"
#include "MemoryLocation.h"
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
    bool add(std::unique_ptr<LocationBase> dest, std::unique_ptr<LocationBase> src, Width w);

    // constexpr static const std::vector<uint8_t> opcodes;
    static bool s_registered;
};

class Operands {
    public:
        Operands(std::unique_ptr<LocationBase>, std::unique_ptr<RegisterLocation>);
        void print();

        std::unique_ptr<LocationBase> E();
        std::unique_ptr<RegisterLocation> G();

        std::unique_ptr<LocationBase> e;
        std::unique_ptr<RegisterLocation> g;
};

Operands decode_modrm(CPU& cpu);


#endif // EXAMPLE_ARITHMETICINSTRUCTION_H
