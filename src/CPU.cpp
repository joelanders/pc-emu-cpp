//
// Created by Joe Landers on 23.05.20.
//

#include "CPU.h"
#include "ArithmeticInstruction.h"
#include "BitwiseInstruction.h"
#include "InstructionFactory.h"
#include "MemoryInstruction.h"
#include "ControlInstruction.h"
#include "util.h"

CPU::CPU() {
    printf("CPU::CPU()\n");
    // registers.set_register(U32, Esp, memory.get_size() - 1);
    // registers.set_register(U32, Ebp, memory.get_size() - 1);
    // XXX the static initialization trick isn't working in the tests
    const std::vector<uint8_t> opcodes{0x00, 0x01, 0x02, 0x03, 0x04, 0x05,
                                       0x10, 0x11, 0x12, 0x13, 0x14, 0x15,
                                       0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d,
                                       0x28, 0x29, 0x2a, 0x2b, 0x2c, 0x2d,
                                       0x38, 0x39, 0x3a, 0x3b, 0x3c, 0x3d,
                                       0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47,
                                       0x48, 0x49, 0x4a, 0x4b, 0x4c, 0x4d, 0x4e, 0x4f,
    };
    InstructionFactory::register_opcodes(opcodes, ArithmeticInstruction::create_method);

    const std::vector<uint8_t> opcodes2{
            0x06, 0x07, 0x0e, 0x0f,
            0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57,
            0x58, 0x59, 0x5a, 0x5b, 0x5c, 0x5d, 0x5e, 0x5f,
            0x88, 0x89, 0x8a, 0x8b,
    };
    InstructionFactory::register_opcodes(opcodes2, MemoryInstruction::create_method);

    const std::vector<uint8_t> opcodes3{0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d,
                                        0x20, 0x21, 0x22, 0x23, 0x24, 0x25};
    InstructionFactory::register_opcodes(opcodes3, BitwiseInstruction::create_method);

    const std::vector<uint8_t> opcodes4{0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77,
        0x78, 0x79, 0x7a, 0x7b, 0x7c, 0x7d, 0x7e, 0x7f};
    InstructionFactory::register_opcodes(opcodes4, ControlInstruction::create_method);

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
    auto maybe_prefix = memory.get_byte(registers.get_eip(), true);
    while (prefix_bytes.count(maybe_prefix)) {
        overrides.emplace_back(maybe_prefix);
        registers.inc_eip();
        maybe_prefix = memory.get_byte(registers.get_eip(), true);
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
    } else {
        throw std::runtime_error("create() failed");
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
    printf("width_to_size(w): %zd\n", width_to_size(w));
    printf("new Esp will be: ");
    print_quad_in_hex(new_esp);
    printf("\n");
    switch (w) {
    case U8:
        memory.set_byte(new_esp, value);
        break;
    case U16:
        memory.set_dual(new_esp, value);
        break;
    case U32:
        memory.set_quad(new_esp, value);
        break;
    default:
        throw std::runtime_error("very bad!");
    }
    registers.set_register(U32, Esp, new_esp); // XXX hard-coding 32-bit here
    return true;
}

std::optional<uint32_t>
CPU::pop_off_stack(Width w) {
    uint32_t old_esp = registers.get_esp();
    uint32_t new_esp = old_esp + width_to_size(w); // XXX think about what overflow behavior we want
    if (new_esp > memory.get_size()) {
        return std::nullopt;
    }
    printf("width_to_size(w): %zd\n", width_to_size(w));
    printf("new Esp will be: ");
    print_quad_in_hex(new_esp);
    printf("\n");
    uint32_t value;
    switch (w) {
    case U8:
        value = memory.get_byte(old_esp, true);
        break;
    case U16:
        value = memory.get_dual(old_esp);
        break;
    case U32:
        value = memory.get_quad(old_esp);
        break;
    default:
        throw std::runtime_error("very bad!");
    }
    registers.set_register(U32, Esp, new_esp); // XXX hard-coding 32-bit here
    return value;
}
