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

std::ostream&
operator<<(std::ostream& os, const CPU& cpu) {
    os << cpu.get_registers() << cpu.get_memory();
    return os;
}

std::ostream&
operator<<(std::ostream& os, const Registers& registers) {
    os << "Registers:" << std::endl;
    os << "\teax: ";
    os << std::setfill('0') << std::setw(8) << std::hex << registers.get_eax() << std::endl;
    os << "\tecx: ";
    os << std::setfill('0') << std::setw(8) << std::hex << registers.get_ecx() << std::endl;
    os << "\tebx: ";
    os << std::setfill('0') << std::setw(8) << std::hex << registers.get_ebx() << std::endl;
    os << "\tedx: ";
    os << std::setfill('0') << std::setw(8) << std::hex << registers.get_edx() << std::endl;
    os << "\teip: ";
    os << std::setfill('0') << std::setw(8) << std::hex << registers.get_eip() << std::endl;
    return os;
}

std::ostream&
operator<<(std::ostream& os, const Memory& memory) {
    os << "Memory:" << std::endl;
    os << "\tsize: " << memory.get_size();
    os << "\n\t";
    print_vector_bytes(memory.get_bytes());
    return os;
}

void
CPU::execute_next_instruction() {
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

    printf("got opcode: ");
    print_byte_in_hex(opcode);
    printf("\n");

    printf("got prefixes: ");
    print_vector_bytes(overrides);
    registers.inc_eip();
}

void
CPU::set_byte(size_t address, uint8_t value) {
    return memory.set_byte(address, value);
}

void
CPU::set_bytes(size_t start, std::string hex_string) {
    return memory.set_bytes(start, hex_string);
}

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

InstructionFactory::InstructionFactory(){};
std::map<uint8_t, InstructionFactory::InstructionConstructor> InstructionFactory::instruction_set{};

bool
InstructionFactory::register_opcode(uint8_t opcode, InstructionConstructor inst_const) {
    if (auto it = instruction_set.find(opcode); it == instruction_set.end()) {
        instruction_set[opcode] = inst_const;
        return true;
    }
    return false;
}

std::unique_ptr<InstructionBase>
InstructionFactory::create(uint8_t opcode) {
    if (auto it = instruction_set.find(opcode); it != instruction_set.end()) {
        std::cout << "CREATING" << std::endl;
        return it->second();
    }
    std::cout << "NOT CREATING" << std::endl;
    return nullptr;
}

ArithmeticInstruction::ArithmeticInstruction(uint8_t opcode, CPU& cpu) : cpu(cpu), opcode(opcode){};

bool
ArithmeticInstruction::execute() {
    std::cout << "SHIIIIIT 000" << std::endl;
    std::cout << "switching on opcode: ";
    print_byte_in_hex(opcode);
    switch (opcode) {
    case 0x00: {
        std::cout << "FUCK 000" << std::endl;
        auto src = MemoryLocation(0x00);
        auto dest = MemoryLocation(0x01);
        return add(src, dest);
    }
    case 0x01: {
        std::cout << "FUCK 111" << std::endl;
        auto src = MemoryLocation(0x00);
        auto dest = RegisterLocation(Eax);
        return add(src, dest); // XXX dummy locations
    }
    }
    return false;
}

bool
ArithmeticInstruction::add(LocationBase& dest, LocationBase& src) {
    dest.write(cpu, U8, dest.read(cpu, U8) + src.read(cpu, U8));
    return true;
}

RegisterLocation::RegisterLocation(Register reg) { reg = reg; }

MemoryLocation::MemoryLocation(uint32_t addy) {
    std::cout << "mem loc constructor with address =  ";
    print_quad_in_hex(addy);
    printf("\n");
    address = addy;
}

uint32_t
RegisterLocation::read(CPU& cpu, Width w) {
    switch (reg) {
    case Eax:
        return cpu.get_registers().get_eax();
        break;
    case Ecx:
        return cpu.get_registers().get_ecx();
        break;
    }
}

uint32_t
RegisterLocation::write(CPU& cpu, Width w, uint32_t value) {
    return 0x69;
}

uint32_t
MemoryLocation::read(CPU& cpu, Width w) {
    std::cout << "mem loc read() from ";
    print_quad_in_hex(address);
    auto b = cpu.get_memory().get_byte(address);
    std::cout << "value is ";
    print_byte_in_hex(b);
    printf("\n");
    return b;
}

uint32_t
MemoryLocation::write(CPU& cpu, Width w, uint32_t value) {
    std::cout << "mem loc write() to addy ";
    print_quad_in_hex(address);
    std::cout << "value ";
    print_quad_in_hex(value);
    printf("\n");
    cpu.set_byte(address, value % 256);
    return 0x69;
}