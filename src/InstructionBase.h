//
// Created by Joe Landers on 23.05.20.
//

#ifndef EXAMPLE_INSTRUCTIONBASE_H
#define EXAMPLE_INSTRUCTIONBASE_H

class CPU;

// abstract base class
class InstructionBase {
  public:
    InstructionBase() = default;
    virtual ~InstructionBase(){};
    virtual bool execute(CPU& cpu) = 0;
};


#endif // EXAMPLE_INSTRUCTIONBASE_H
