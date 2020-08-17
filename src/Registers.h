//
// Created by Joe Landers on 23.05.20.
//

#ifndef EXAMPLE_REGISTERS_H
#define EXAMPLE_REGISTERS_H

#include "util.h"

class Registers {
  public:
    Registers();
    virtual ~Registers(){};
    uint32_t get_eax() const { return eax; }
    uint32_t get_ecx() const { return ecx; }
    uint32_t get_edx() const { return edx; }
    uint32_t get_ebx() const { return ebx; }

    uint32_t get_esp() const { return esp; }
    uint32_t get_ebp() const { return ebp; }
    uint32_t get_esi() const { return esi; }
    uint32_t get_edi() const { return edi; }

    uint32_t get_eip() const { return eip; }

    uint32_t get_ss() const { return ss; }
    uint32_t get_cs() const { return cs; }
    uint32_t get_ds() const { return ds; }
    uint32_t get_es() const { return es; }
    uint32_t get_fs() const { return fs; }
    uint32_t get_gs() const { return gs; }

    bool set_register(Width w, Register reg, uint32_t value);
    void inc_eip() { ++eip; }

    uint32_t get_register_by_index(size_t index, Width w);

  private:
    uint32_t eax;
    uint32_t ecx;
    uint32_t edx;
    uint32_t ebx;

    uint32_t esp;
    uint32_t ebp;
    uint32_t esi;
    uint32_t edi;

    uint32_t eip;

    uint32_t ss;
    uint32_t cs;
    uint32_t ds;
    uint32_t es;
    uint32_t fs;
    uint32_t gs;
};


std::ostream&
operator<<(std::ostream& os, Registers const& registers);


#endif // EXAMPLE_REGISTERS_H
