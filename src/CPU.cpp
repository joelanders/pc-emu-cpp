//
// Created by Joe Landers on 23.05.20.
//

#include "CPU.h"
#include "util.h"
#include "InstructionFactory.h"
#include "ArithmeticInstruction.h"
#include "MemoryInstruction.h"

CPU::CPU() {
    printf("CPU::CPU()\n");
    // XXX the static initialization trick isn't working in the tests
    const std::vector<uint8_t> opcodes { 0x00, 0x01, 0x02, 0x03 };
    InstructionFactory::register_opcodes(opcodes, ArithmeticInstruction::create_method);

    const std::vector<uint8_t> opcodes2 { 0x06, 0x07 };
    InstructionFactory::register_opcodes(opcodes2, MemoryInstruction::create_method);
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
        bool success = instruction->execute(*this);
        if (!success) {
            printf("execute() returned false!\n");
        }
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

void
CPU::set_register(Width w, Register reg, uint32_t value) {
    registers.set_register(w, reg, value);
}

bool
CPU::push_on_stack(Width w, uint32_t value) {
    int32_t new_esp = registers.get_esp() - width_to_size(w);
    if (new_esp < 0) {
        return false;
    }
    printf("new Esp will be: ");
    print_quad_in_hex(new_esp);
    printf("\n");
    switch (w) {
        case U8:
            memory.set_byte(new_esp, value);
            break;
        case U16:
            throw std::runtime_error("u16 not implemented");
        case U32:
            memory.set_quad(new_esp, value);
            break;
        default:
            throw std::runtime_error("very bad!");
    }
    registers.set_register(U32, Esp, new_esp);  // XXX hard-coding 32-bit here
    return true;
}

std::optional<uint32_t> 
CPU::pop_off_stack(Width w) {
    uint32_t old_esp = registers.get_esp();
    uint32_t new_esp = old_esp + width_to_size(w);  // XXX think about what overflow behavior we want
    if (new_esp > memory.get_size()) {
        return std::nullopt;
    }
    printf("new Esp will be: ");
    print_quad_in_hex(new_esp);
    printf("\n");
    uint32_t value;
    switch (w) {
        case U8:
            value = memory.get_byte(old_esp);
            break;
        case U16:
            throw std::runtime_error("u16 not implemented");
        case U32:
            value = memory.get_quad(old_esp);
            break;
        default:
            throw std::runtime_error("very bad!");
    }
    registers.set_register(U32, Esp, new_esp);  // XXX hard-coding 32-bit here
    return value;
}
