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

uint32_t
Memory::get_byte(size_t address) {
    if (address + 1 > bytes.size()) {
        bytes.resize(address + 1);
    }

    return bytes.at(address);
}

uint32_t
Memory::get_quad(size_t address) {
    uint32_t value = 0;
    value += bytes.at(address);
    value += bytes.at(address + 1) << 8;
    value += bytes.at(address + 2) << 16;
    value += bytes.at(address + 3) << 24;
    return value;
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
        uint8_t byte = strtol(hex_digit.c_str(), NULL, 16);
        bytes[i] = byte;
        ++i;
    }
}

void
Memory::set_bytes(size_t start, std::vector<uint8_t> new_bytes) {
    if (start + new_bytes.size() > bytes.size()) {
        bytes.resize(start + new_bytes.size());
    }

    size_t i = start;
    for (auto& byte : new_bytes) {
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
