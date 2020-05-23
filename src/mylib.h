#pragma once

#include <cstdint>
#include <map>
#include <vector>
#include <iostream>
#include <set>
#include <sstream>
#include <iomanip>
#include <cstdio>
#include <boost/algorithm/string.hpp>



void
print_vector_bytes(std::vector<uint8_t> const& v);

void
print_byte_in_hex(uint8_t byte);

void
print_quad_in_hex(uint32_t quad);


enum Register { Eax, Ecx, Ebx, Edx, Eip, Esp };
enum Width { U8, U16, U32 };

