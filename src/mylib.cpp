#include "mylib.h"
#include <cstdint>
#include <cstdio>
#include <iomanip>
#include <iostream>
#include <sstream>

#include <set>
#include <vector>

#include <boost/algorithm/string.hpp>

Memory::Memory() : bytes(0) {}
Registers::Registers() : eip(0) {}
CPU::CPU() {}

void print_vector_bytes(std::vector<uint8_t> const& v) {
    for (auto& b : v) {
        std::cout << std::setfill('0') << std::setw(2) << std::hex << b << " ";
    }
}

std::ostream& operator<<(std::ostream& os, const CPU& cpu) {
    os << cpu.get_registers() << cpu.get_memory();
    return os;
}

std::ostream& operator<<(std::ostream& os, const Registers& registers) {
    os << "Registers:" << std::endl;
    os << "\teax: ";
    os << std::setfill('0') << std::setw(8) << std::hex << registers.get_eax() << std::endl;
    os << "\tecx: ";
    os << std::setfill('0') << std::setw(8) << std::hex << registers.get_ecx() << std::endl;
    return os;
}

std::ostream& operator<<(std::ostream& os, const Memory& memory) {
    os << "Memory:" << std::endl;
    os << "\tsize: " << memory.get_size();
    os << "\n\t";
    print_vector_bytes(memory.get_bytes());
    return os;
}

void CPU::execute_next_instruction() {
    // auto opcode = memory
    std::set<uint8_t> prefix_bytes{0x2e, 0x36, 0x3e, 0x26, 0x64, 0x65};

    uint8_t opcode;
    std::vector<uint8_t> overrides{};
    auto maybe_prefix = memory.get_byte(registers.get_eip());
    while (prefix_bytes.count(maybe_prefix)) {
        overrides.emplace_back(maybe_prefix);
        registers.inc_eip();
        maybe_prefix = memory.get_byte(registers.get_eip());
    }
    opcode = maybe_prefix;

    std::cout << "got opcode:" << opcode << std::endl;
    std::cout << "got prefixes: ";
    print_vector_bytes(overrides);
}

void Memory::set_bytes(size_t start, std::string hex_string) {
    std::vector<std::string> hexes;
    boost::split(hexes, hex_string, boost::is_any_of(" "));
    if (start + hexes.size() > bytes.size()) {
        bytes.resize(start + hexes.size());
    }

    size_t i = 0;
    for (auto& hex_digit : hexes) {
        std::stringstream ss;
        std::cout << "fuck: " << hex_digit << std::endl;
        ss << std::hex << hex_digit;
        ss >> bytes[i];
        ++i;
    }
}
