//
// Created by Joe Landers on 23.05.20.
//

#ifndef EXAMPLE_REGISTERS_H
#define EXAMPLE_REGISTERS_H

#include "mylib.h"
#include "Addressable.h"


class Registers : public Addressable {
  public:
    Registers();
    virtual ~Registers(){};
    uint32_t get_eax() const { return eax; }
    uint32_t get_ecx() const { return ecx; }
    uint32_t get_ebx() const { return ebx; }
    uint32_t get_edx() const { return edx; }
    uint32_t get_eip() const { return eip; }
    void inc_eip() { ++eip; }

  private:
    uint32_t eax;
    uint32_t ecx;
    uint32_t ebx;
    uint32_t edx;
    uint32_t eip;
};


std::ostream&
operator<<(std::ostream& os, Registers const& registers);


#endif // EXAMPLE_REGISTERS_H
