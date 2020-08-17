//
// Created by Joe Landers on 28.06.20.
//

#include "util.h"


void
print_vector_bytes(std::vector<uint8_t> const& v) {
    size_t i = 0;
    for (auto& b : v) {
        if (i++ % 16 == 0) {
            printf("\n\t");
        }
        printf("%02x ", b);
    }
    printf("\n");
}

void
print_byte_in_hex(uint8_t byte) {
    printf("%02x ", byte);
}

void
print_quad_in_hex(uint32_t quad) {
    printf("%08x ", quad);
}

Register
index_to_register(uint8_t index) {
    printf("register index is: %02x\n", index);
    switch (index) {
    case 0b000:
        return Eax;
    case 0b001:
        return Ecx;
    case 0b010:
        return Edx;
    case 0b011:
        return Ebx;
    case 0b100:
        return Esp;
    case 0b101:
        return Ebp;
    case 0b110:
        return Esi;
    case 0b111:
        return Edi;
    }
    printf("XXXXXXX BAD (index_to_register) XXXXXXX");
}

void
print_width(Width w) {
    switch (w) {
    case U8:
        printf("U8 ");
        return;
    case U16:
        printf("U16 ");
        return;
    case U32:
        printf("U32 ");
        return;
    }
}

size_t
width_to_size(Width w) {
    switch (w) {
    case U8:
        return 1;
    case U16:
        return 2;
    case U32:
        return 4;
    }
}

void
print_register(Register r) {
    switch (r) {
    case Eax:
        printf("Eax ");
        return;
    case Ecx:
        printf("Ecx ");
        return;
    case Edx:
        printf("Edx ");
        return;
    case Ebx:
        printf("Ebx ");
        return;
    case Esp:
        printf("Esp ");
        return;
    case Ebp:
        printf("Ebp ");
        return;
    case Esi:
        printf("Esi ");
        return;
    case Edi:
        printf("Edi ");
        return;
    case Eip:
        printf("Eip ");
        return;
    }
    printf("XXXXXXX BAD (print_register) XXXXXXX");
}

