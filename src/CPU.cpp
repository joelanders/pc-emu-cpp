//
// Created by Joe Landers on 23.05.20.
//

#include "CPU.h"
#include "util.h"
#include "InstructionFactory.h"
#include "ArithmeticInstruction.h"

CPU::CPU() {
    printf("CPU::CPU()\n");
    // XXX the static initialization trick isn't working in the tests
    const std::vector<uint8_t> opcodes { 0x00, 0x01, 0x02, 0x03 };
    InstructionFactory::register_opcodes(opcodes, ArithmeticInstruction::create_method);
}

std::ostream&
operator<<(std::ostream& os, const CPU& cpu) {
    os << cpu.get_registers() << cpu.get_memory();
    return os;
}

void
CPU::execute_next_instruction() {
    printf("execute_next_instruction(), eip: ");
    print_quad_in_hex(registers.get_eip());
    printf("\n");
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
    registers.inc_eip();

    printf("got opcode: ");
    print_byte_in_hex(opcode);
    printf("\n");

    printf("got prefixes: ");
    print_vector_bytes(overrides);

    auto instruction = InstructionFactory::create(opcode, *this);
    if (instruction) {
        instruction->execute(*this);
    }
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
CPU::set_bytes(size_t start, std::vector<uint8_t> bytes) {
    return memory.set_bytes(start, bytes);
}

bool
CPU::set_register(Width w, Register reg, uint32_t value) {
    registers.set_register(w, reg, value);
}
