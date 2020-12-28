//
// Created by Joe Landers on 28.12.20.
//

#include "ControlInstruction.h"
#include "InstructionFactory.h"

ControlInstruction::ControlInstruction(uint8_t opcode, CPU& cpu) : cpu(cpu), opcode(opcode){};

bool
ControlInstruction::execute(CPU& cpu) {
    std::cout << "ControlInstruction::execute " << std::endl;
    std::cout << "opcode: ";
    print_byte_in_hex(opcode);
    printf("\n");
    int8_t offset = cpu.get_memory().get_byte(cpu.get_registers().get_eip(), true);
    cpu.get_registers().inc_eip();

    switch (opcode) {
    case 0x70: {
        // jump short if overflow (OF = 1)
        if (!cpu.get_registers().get_of()) {
            printf("not jumping\n");
            return true;
        }
        break;
    }
    case 0x71: {
        // jump short if NOT overflow
        if (cpu.get_registers().get_of()) {
            printf("not jumping\n");
            return true;
        }
        break;
    }
    case 0x72: {
        // jump short if below (CF = 1)
        if (!cpu.get_registers().get_cf()) {
            printf("not jumping\n");
            return true;
        }
        break;
    }
    case 0x73: {
        // jump short if NOT below
        if (cpu.get_registers().get_cf()) {
            printf("not jumping\n");
            return true;
        }
        break;
    }
    case 0x74: {
        // jump short if zero (ZF = 1)
        if (!cpu.get_registers().get_zf()) {
            printf("not jumping\n");
            return true;
        }
        break;
    }
    case 0x75: {
        // jump short if NOT zero
        if (cpu.get_registers().get_zf()) {
            printf("not jumping\n");
            return true;
        }
        break;
    }
    case 0x76: {
        // jump short if below or equal (CF = 1 or ZF = 1)
        if (!cpu.get_registers().get_cf() && !cpu.get_registers().get_zf()) {
            printf("not jumping\n");
            return true;
        }
        break;
    }
    case 0x77: {
        // jump short if NOT below or equal (CF = 0 and ZF = 0)
        if (cpu.get_registers().get_cf() || cpu.get_registers().get_zf()) {
            printf("not jumping\n");
            return true;
        }
        break;
    }
    case 0x78: {
        // jump short if sign (SF = 1)
        if (!cpu.get_registers().get_sf()) {
            printf("not jumping\n");
            return true;
        }
        break;
    }
    case 0x79: {
        // jump short if NOT sign
        if (cpu.get_registers().get_sf()) {
            printf("not jumping\n");
            return true;
        }
        break;
    }
    case 0x7a: {
        // jump short if parity (PF = 1)
        if (!cpu.get_registers().get_pf()) {
            printf("not jumping\n");
            return true;
        }
        break;
    }
    case 0x7b: {
        // jump short if NOT parity
        if (cpu.get_registers().get_pf()) {
            printf("not jumping\n");
            return true;
        }
        break;
    }
    case 0x7c: {
        // jump short if less (SF != OF)
        if (cpu.get_registers().get_sf() == cpu.get_registers().get_of()) {
            printf("not jumping\n");
            return true;
        }
        break;
    }
    case 0x7d: {
        // jump short if NOT less
        if (cpu.get_registers().get_sf() != cpu.get_registers().get_of()) {
            printf("not jumping\n");
            return true;
        }
        break;
    }
    case 0x7e: {
        // jump short if less or equal (SF != OF or ZF = 1)
        if ((cpu.get_registers().get_sf() == cpu.get_registers().get_of()) && cpu.get_registers().get_zf()) {
            printf("not jumping\n");
            return true;
        }
        break;
    }
    case 0x7f: {
        // jump short if NOT less or equal (SF == OF and ZF = 0)
        if ((cpu.get_registers().get_sf() != cpu.get_registers().get_of()) || cpu.get_registers().get_zf()) {
            printf("not jumping\n");
            return true;
        }
        break;
    }
    }

    // XXX int_t vs uint_t bullshit
    if (offset < 0) {
        uint32_t source = cpu.get_registers().get_eip();
        uint32_t destination = source + offset;
        cpu.get_registers().set_eip(destination);
        printf("jumping back %d bytes, from %u to %u", offset, source, destination);
    } else {
        uint32_t source = cpu.get_registers().get_eip();
        uint32_t destination = source + offset;
        cpu.get_registers().set_eip(destination);
        printf("jumping forward %d bytes, from %u to %u", offset, source, destination);
    }

    return true;

}

// XXX SIGSEV if i have this in... jesus christ
// const std::vector<uint8_t> opcodes{0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77,
//                                   0x78, 0x79, 0x7a, 0x7b, 0x7c, 0x7d, 0x7e, 0x7f};

// bool ControlInstruction::s_registered =
//    InstructionFactory::register_opcodes(opcodes, ControlInstruction::create_method);