//
// Created by Joe Landers on 23.05.20.
//

#ifndef EXAMPLE_ARITHMETICINSTRUCTION_H
#define EXAMPLE_ARITHMETICINSTRUCTION_H

#include "InstructionBase.h"
#include "LocationBase.h"
#include "MemoryLocation.h"
#include "RegisterLocation.h"
#include "mylib.h"

class ArithmeticInstruction : public InstructionBase {
  public:
    ArithmeticInstruction(uint8_t opcode, CPU& cpu);
    virtual ~ArithmeticInstruction(){};
    virtual bool execute();

  private:
    uint8_t opcode;
    CPU& cpu;
    bool add(LocationBase& dest, LocationBase& src);
};


#endif // EXAMPLE_ARITHMETICINSTRUCTION_H
