#include <cstdio>
#include <iostream>

#include "CPU.h"
#include "config.h"

int
main(int argc, char** argv) {
    printf("program version: %i.%i.%i\n", VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH);
    printf("git hash: %s\n", GIT_REVISION);

    CPU cpu;

    for (int i = 1; i < argc; i++) {
        if (std::string(argv[i]) == "--memory") {
            if (i + 2 > argc) {
                std::cout << "--memory expects two args after";
                return -1;
            }
            char* mem_start_string = argv[++i];
            uint32_t mem_start = std::atoi(mem_start_string);
            std::string hex_string = argv[++i];
            cpu.get_memory().set_bytes(mem_start, hex_string);
        } else if (std::string(argv[i]) == "--register") {
            if (i + 2 > argc) {
                std::cout << "--register expects two args after";
                return -1;
            }
            uint8_t reg_index = std::stoi(argv[++i]);
            uint32_t reg_value = std::stol(argv[++i], nullptr, 0);
            cpu.get_registers().set_register(U32, index_to_register(reg_index), reg_value);
        } else if (std::string(argv[i]) == "--mem-size") {
            if (i + 1 > argc) {
                std::cout << "--mem-size expects an argument after";
                return -1;
            }
            uint32_t mem_size = std::stol(argv[++i], nullptr, 0);
            cpu.get_memory().set_size(mem_size);
            cpu.get_registers().set_register(U32, Esp, mem_size - 1);  // XXX ugly
            cpu.get_registers().set_register(U32, Ebp, mem_size - 1);
        } else {
            std::cout << "didn't recognize the flag";
            return -1;
        }
    }
    std::cout << "  --- start: ---" << std::endl;
    cpu.execute_next_instruction();
    std::cout << "  --- after: ---" << std::endl;
    std::cout << "EIP:        ";
    print_quad_in_hex(cpu.get_registers().get_eip());
    printf("\n");
    std::cout << "EFLAGS: XXX" << std::endl;
    std::cout << "REGS1: ";
    for (int i = 0; i < 8; i++) {
        print_register(index_to_register(i), U32);
        printf(": ");
        print_quad_in_hex(cpu.get_registers().get_register_by_index(i, U32));
    }
    printf("\n");
    std::cout << "REGS2: ";
    for (int i = 0; i < 8; i++) {
        printf(" ");
        print_register(index_to_register(i), U16);
        printf(":     ");
        print_double_in_hex(cpu.get_registers().get_register_by_index(i, U16));
    }
    printf("\n");

    // std::cout << cpu << std::endl;

    // cpu.get_memory().set_bytes(0, "01 02 03 04");
    // std::cout << cpu << std::endl;

    // cpu.get_memory().set_bytes(4, "05 06 07 08");
    // std::cout << cpu << std::endl;

    // cpu.get_memory().set_bytes(8, "01 02 00 02");
    // std::cout << cpu << std::endl;

    // cpu.get_memory().set_bytes(12, "02 03 03 03");
    // std::cout << cpu << std::endl;

    // cpu.get_memory().set_zero_bytes(20, 20);
    // std::cout << cpu << std::endl;

    // cpu.get_registers().set_register(U32, Eax, 0x08);
    // cpu.get_registers().set_register(U32, Ecx, 0x09);
    // cpu.get_registers().set_register(U32, Edx, 0x0a);
    // cpu.get_registers().set_register(U32, Ebx, 0x0b);
    // cpu.get_registers().set_register(U32, Esp, 0x0c);
    // cpu.get_registers().set_register(U32, Ebp, 0x0d);
    // cpu.get_registers().set_register(U32, Esi, 0x0e);
    // cpu.get_registers().set_register(U32, Edi, 0x0f);

    // cpu.execute_next_instruction();
    // cpu.execute_next_instruction();
    // cpu.execute_next_instruction();
    // cpu.execute_next_instruction();
    // cpu.execute_next_instruction();
    // cpu.execute_next_instruction();
    // cpu.execute_next_instruction();
    // cpu.execute_next_instruction();
    // cpu.execute_next_instruction();
    // cpu.execute_next_instruction();

    // auto instruction = InstructionFactory::create(0x00, cpu);
    // instruction->execute(cpu);
    // std::cout << cpu << std::endl;

    // instruction = InstructionFactory::create(0x01, cpu);
    // instruction->execute(cpu);
    // std::cout << cpu << std::endl;


    return 0;
}
