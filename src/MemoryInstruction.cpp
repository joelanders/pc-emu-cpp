#include "MemoryInstruction.h"
#include "util.h"

MemoryInstruction::MemoryInstruction(uint8_t opcode, CPU& cpu) : cpu(cpu), opcode(opcode){};

bool
MemoryInstruction::execute(CPU& cpu) {
    std::cout << "MemoryInstruction::execute " << std::endl;
    std::cout << "switching on opcode: ";
    print_byte_in_hex(opcode);
    printf("\n");
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
        return cpu.push_on_stack(U32, cpu.get_registers().get_cs());
    }
    case 0x0f: {
        auto val = cpu.pop_off_stack(cpu.current_value_size);
        if (!val) {
            return false; // XXX stack overflow
        }
        cpu.set_register(U32, Cs, val.value());
        return true;
    }
    case 0x50 ... 0x57: {
        Width w = U32; // XXX account for other sizes
        uint8_t reg_index = opcode & 0b111;
        return cpu.push_on_stack(w, cpu.get_registers().get_register_by_index(reg_index, w));
    }
    case 0x58 ... 0x5f: {
        Width w = U32;
        uint8_t reg_index = opcode & 0b111;
        auto val = cpu.pop_off_stack(w);
        if (!val) {
            return false; // XXX stack overflow
        }
        cpu.set_register(w, index_to_register(reg_index, w), val.value());
        return true;
    }
    }
    throw std::runtime_error("reached end of MemoryInstruction::execute()");
}

const std::vector<uint8_t> opcodes{0x06, 0x07, 0x0e, 0x0f,
                                   0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57,
                                   0x58, 0x59, 0x5a, 0x5b, 0x5c, 0x5d, 0x5e, 0x5f,
};

// bool
// MemoryInstruction::s_registered =
//     InstructionFactory::register_opcodes(opcodes,
//                                          MemoryInstruction::create_method);
