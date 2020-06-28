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


enum Register { Eax, Ecx, Edx, Ebx,  Esp, Ebp, Esi, Edi,  Eip };
enum Width { U8, U16, U32 };

Register
index_to_register(uint8_t index);

void
print_width(Width w);

void
print_register(Register r);

#endif // EXAMPLE_UTIL_H
