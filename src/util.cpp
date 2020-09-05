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

void
print_double_in_hex(uint32_t dub) {
    printf("%04x ", dub);
}

Register
index_to_register(uint8_t index) {
    // printf("register index is: %02x\n", index);
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

uint8_t
register_to_index(Register reg) {
    // printf("register index is: %02x\n", index);
    switch (reg) {
    case Eax:
        return 0;
    case Ecx:
        return 1;
    case Edx:
        return 2;
    case Ebx:
        return 3;
    case Esp:
        return 4;
    case Ebp:
        return 5;
    case Esi:
        return 6;
    case Edi:
        return 7;
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
print_register(Register r, Width wid) {
    switch (wid) {
    case U8:
        switch (r) {
        case Eax:
            printf("al");
            return;
        case Ecx:
            printf("cl");
            return;
        case Edx:
            printf("dl");
            return;
        case Ebx:
            printf("bl");
            return;
        case Esp:
            printf("spl");
            return;
        case Ebp:
            printf("bpl");
            return;
        case Esi:
            printf("sil");
            return;
        case Edi:
            printf("dil");
            return;
        }
    case U16:
        switch (r) {
        case Eax:
            printf("ax");
            return;
        case Ecx:
            printf("cx");
            return;
        case Edx:
            printf("dx");
            return;
        case Ebx:
            printf("bx");
            return;
        case Esp:
            printf("sp");
            return;
        case Ebp:
            printf("bp");
            return;
        case Esi:
            printf("si");
            return;
        case Edi:
            printf("di");
            return;
        }
    case U32:
        switch (r) {
        case Eax:
            printf("eax");
            return;
        case Ecx:
            printf("ecx");
            return;
        case Edx:
            printf("edx");
            return;
        case Ebx:
            printf("ebx");
            return;
        case Esp:
            printf("esp");
            return;
        case Ebp:
            printf("ebp");
            return;
        case Esi:
            printf("esi");
            return;
        case Edi:
            printf("edi");
            return;
        case Eip:
            printf("eip");
            return;
        }
    }
    printf("XXXXXXX BAD (print_register) XXXXXXX");
}
