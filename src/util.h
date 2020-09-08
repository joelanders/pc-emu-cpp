//
// Created by Joe Landers on 28.06.20.
//

#ifndef EXAMPLE_UTIL_H
#define EXAMPLE_UTIL_H

#include <boost/algorithm/string.hpp>
#include <cstdint>
#include <cstdio>
#include <iomanip>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <vector>


void
print_vector_bytes(std::vector<uint8_t> const& v);

void
print_byte_in_hex(uint8_t byte);

void
print_quad_in_hex(uint32_t quad);

void
print_double_in_hex(uint32_t dub);

enum Register { Eax, Ecx, Edx, Ebx,
                Al,  Cl,  Dl,  Bl,
                Ah,  Ch,  Dh,  Bh,
                Esp, Ebp, Esi, Edi,
                Eip,
                Ss, Cs, Ds, Es, Fs, Gs
};

enum Width { U8, U16, U32 };

Register
index_to_register(uint8_t index, Width w);

Register
index_to_segment_register(uint8_t index);

uint8_t
register_to_index(Register reg, Width w);

uint8_t
segment_register_to_index(Register reg);

void
print_width(Width w);

void
print_register(Register r, Width wid);

size_t
width_to_size(Width w);

#endif // EXAMPLE_UTIL_H
