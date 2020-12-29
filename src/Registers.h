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

    bool get_cf() const { return cf; }
    bool get_pf() const { return pf; }
    bool get_af() const { return af; }
    bool get_zf() const { return zf; }
    bool get_sf() const { return sf; }
    bool get_tf() const { return tf; }
    bool get_if() const { return if_; }
    bool get_df() const { return df; }
    bool get_of() const { return of; }

    void set_cf(bool new_val) { cf = new_val; }
    void set_pf(bool new_val) { pf = new_val; }
    void set_af(bool new_val) { af = new_val; }
    void set_zf(bool new_val) { zf = new_val; }
    void set_sf(bool new_val) { sf = new_val; }
    void set_tf(bool new_val) { tf = new_val; }
    void set_if(bool new_val) { if_ = new_val; }
    void set_df(bool new_val) { df = new_val; }
    void set_of(bool new_val) { of = new_val; }

    void update_status_flags(uint64_t a, uint64_t b, uint64_t c, Width w, bool flip_sign, bool no_af, bool zero_of_cf,
                             bool no_cf);
    void print_status_flags();
    bool set_register(Width w, Register reg, uint32_t value, bool silent=false);
    bool set_segment_register(Register reg, uint32_t value);
    void inc_eip() { ++eip; }
    void set_eip(uint32_t new_val) { eip = new_val; }

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

    bool cf;
    bool pf;
    bool af;
    bool zf;
    bool sf;
    bool tf;
    bool if_;
    bool df;
    bool of;
};


std::ostream&
operator<<(std::ostream& os, Registers const& registers);


#endif // EXAMPLE_REGISTERS_H
