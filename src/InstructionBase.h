//
// Created by Joe Landers on 23.05.20.
//

#ifndef EXAMPLE_INSTRUCTIONBASE_H
#define EXAMPLE_INSTRUCTIONBASE_H


// abstract base class
class InstructionBase {
  public:
    InstructionBase() = default;
    virtual ~InstructionBase(){};
    virtual bool execute() = 0;
};


#endif // EXAMPLE_INSTRUCTIONBASE_H
