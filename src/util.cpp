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
index_to_register(uint8_t index, Width w) {
    // printf("register index is: %02x\n", index);
    if (w == U8) {
        switch (index) {
        case 0b000:
            return Al;
        case 0b001:
            return Cl;
        case 0b010:
            return Dl;
        case 0b011:
            return Bl;
        case 0b100:
            return Ah;
        case 0b101:
            return Ch;
        case 0b110:
            return Dh;
        case 0b111:
            return Bh;
        }
    }
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
    throw std::runtime_error("index_to_register() index not found: " + std::to_string(index));
}

Register
index_to_segment_register(uint8_t index) {
    switch (index) {
    case 0:
        return Ss;
    case 1:
        return Cs;
    case 2:
        return Ds;
    case 3:
        return Es;
    case 4:
        return Fs;
    case 5:
        return Gs;
    }
    printf("XXXXXXX BAD (index_to_segment_register) XXXXXXX");
    throw std::runtime_error("index_to_segment_register() index not found: " + std::to_string(index));
}

uint8_t
register_to_index(Register reg, Width w) {
    if (w == U8) {
        switch (reg) {
        case Al:
            return 0;
        case Cl:
            return 1;
        case Dl:
            return 2;
        case Bl:
            return 3;
        case Ah:
            return 4;
        case Ch:
            return 5;
        case Dh:
            return 6;
        case Bh:
            return 7;
        default:
            throw std::runtime_error("register_to_index() U8 reg not found: " + reg);
        }
    }
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
    printf("XXXXXXX BAD (register_to_index) XXXXXXX");
    throw std::runtime_error("register_to_index() reg not found: " + reg);
}

uint8_t
segment_register_to_index(Register reg) {
    // XXX do the segment registers belong here? it's just convenient for now
    switch (reg) {
    case Ss:
        return 0;
    case Cs:
        return 1;
    case Ds:
        return 2;
    case Es:
        return 3;
    case Fs:
        return 4;
    case Gs:
        return 5;
    }
    printf("XXXXXXX BAD (segment_register_to_index) XXXXXXX");
    print_register(reg, U32);
    throw std::runtime_error("segment_register_to_index() reg not found: " + reg);
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
        case Al:
            printf("al");
            return;
        case Cl:
            printf("cl");
            return;
        case Dl:
            printf("dl");
            return;
        case Bl:
            printf("bl");
            return;
        case Ah:
            printf("ah");
            return;
        case Ch:
            printf("ch");
            return;
        case Dh:
            printf("dh");
            return;
        case Bh:
            printf("bh");
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
    throw std::runtime_error("print_register() reached end");
}
