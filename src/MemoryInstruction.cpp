#include "MemoryInstruction.h"
#include "util.h"

MemoryInstruction::MemoryInstruction(uint8_t opcode, CPU& cpu) : cpu(cpu), opcode(opcode){};

bool
MemoryInstruction::execute(CPU& cpu) {
    std::cout << "MemoryInstruction::execute " << std::endl;
    std::cout << "switching on opcode: ";
    print_byte_in_hex(opcode);
    switch (opcode) {
    case 0x06: {
        return cpu.push_on_stack(U32, cpu.get_registers().get_es());
    }
    case 0x07: {
        auto val = cpu.pop_off_stack(U32);
        if (!val) {
            return false; // XXX stack overflow
        }
        cpu.set_register(U32, Es, val.value());
        return true;
    }
    case 0x0e: {
        return cpu.push_on_stack(cpu.current_value_size, cpu.get_registers().get_cs());
    }
    case 0x0f: {
        auto val = cpu.pop_off_stack(cpu.current_value_size);
        if (!val) {
            return false; // XXX stack overflow
        }
        cpu.set_register(cpu.current_value_size, Cs, val.value());
        return true;
    }
    }
}

const std::vector<uint8_t> opcodes{0x06, 0x07, 0x0e, 0x0f};

// bool
// MemoryInstruction::s_registered =
//     InstructionFactory::register_opcodes(opcodes,
//                                          MemoryInstruction::create_method);
