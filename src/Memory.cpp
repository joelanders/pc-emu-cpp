//
// Created by Joe Landers on 23.05.20.
//

#include "Memory.h"

Memory::Memory() : bytes(0) {}

void
Memory::set_byte(size_t address, uint8_t value) {
    if (address + 1 > bytes.size()) {
        bytes.resize(address + 1);
    }

    bytes[address] = value;
}

void
Memory::set_bytes(size_t start, std::string hex_string) {
    std::vector<std::string> hexes;
    boost::split(hexes, hex_string, boost::is_any_of(" "));

    if (start + hexes.size() > bytes.size()) {
        bytes.resize(start + hexes.size());
    }

    size_t i = start;
    for (auto& hex_digit : hexes) {
        std::stringstream ss;
        std::cout << "fuck: " << hex_digit << std::endl;
        uint8_t byte = strtol(hex_digit.c_str(), NULL, 16);
        bytes[i] = byte;
        ++i;
    }
}

void
Memory::set_zero_bytes(size_t start, size_t len) {
    if (start + len > bytes.size()) {
        bytes.resize(start + len);
    }

    for (size_t i = start; i < len; i++) {
        bytes[i] = 0;
    }
}

std::ostream&
operator<<(std::ostream& os, const Memory& memory) {
    os << "Memory:" << std::endl;
    os << "\tsize: " << memory.get_size();
    os << "\n\t";
    print_vector_bytes(memory.get_bytes());
    return os;
}
