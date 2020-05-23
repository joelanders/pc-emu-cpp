#include "mylib.h"


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
