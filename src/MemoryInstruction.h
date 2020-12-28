#ifndef EXAMPLE_MEMORYINSTRUCTION_H
#define EXAMPLE_MEMORYINSTRUCTION_H

#include "CPU.h"
#include "InstructionBase.h"
#include "InstructionFactory.h"
#include "RegisterLocation.h"

class MemoryInstruction : public InstructionBase {
  public:
    MemoryInstruction(uint8_t opcode, CPU& cpu);
    virtual ~MemoryInstruction(){};
    virtual bool execute(CPU& cpu);
    bool mov(std::unique_ptr<LocationBase> dest, std::unique_ptr<LocationBase> src, Width w);

    static std::unique_ptr<InstructionBase> create_method(uint8_t opcode, CPU& cpu) {
        return std::make_unique<MemoryInstruction>(opcode, cpu);
    }

  private:
    uint8_t opcode;
    CPU& cpu;
    static bool s_registered;
};

#endif // EXAMPLE_MEMORYINSTRUCTION_H
