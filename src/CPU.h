//
// Created by Joe Landers on 23.05.20.
//

#ifndef EXAMPLE_CPU_H
#define EXAMPLE_CPU_H

#include "Memory.h"
#include "Registers.h"
#include "util.h"

class CPU {
  public:
    CPU();
    void execute_next_instruction();
    const Registers& get_registers() const { return registers; };
    const Memory& get_memory() const { return memory; };

    Registers& get_registers() { return registers; };
    Memory& get_memory() { return memory; };

    void set_byte(size_t address, uint8_t value);
    void set_bytes(size_t start, std::string hex_string);
    void set_bytes(size_t start, std::vector<uint8_t> bytes);

    bool set_register(Width w, Register reg, uint32_t value);

  private:
    Registers registers;
    Memory memory;
};

std::ostream&
operator<<(std::ostream& os, CPU const& cpu);


#endif // EXAMPLE_CPU_H
