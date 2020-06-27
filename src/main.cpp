#include <cstdio>
#include <iostream>

#include "ArithmeticInstruction.h"
#include "InstructionFactory.h"
#include "config.h"
#include "mylib.h"

int
main(int argc, char** argv) {
    printf("program version: %i.%i.%i\n", VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH);
    printf("git hash: %s\n", GIT_REVISION);

    CPU cpu;
    std::cout << cpu << std::endl;

    cpu.get_memory().set_bytes(0, "01 02 03 04");
    std::cout << cpu << std::endl;

    cpu.get_memory().set_bytes(4, "05 06 07 08");
    std::cout << cpu << std::endl;

    cpu.get_memory().set_bytes(8, "01 02 00 02");
    std::cout << cpu << std::endl;

    cpu.get_memory().set_bytes(12, "02 03 03 03");
    std::cout << cpu << std::endl;

    cpu.get_memory().set_zero_bytes(20, 20);
    std::cout << cpu << std::endl;

    cpu.get_registers().set_register(U32, Eax, 0x08);
    cpu.get_registers().set_register(U32, Ecx, 0x09);
    cpu.get_registers().set_register(U32, Edx, 0x0a);
    cpu.get_registers().set_register(U32, Ebx, 0x0b);
    cpu.get_registers().set_register(U32, Esp, 0x0c);
    cpu.get_registers().set_register(U32, Ebp, 0x0d);
    cpu.get_registers().set_register(U32, Esi, 0x0e);
    cpu.get_registers().set_register(U32, Edi, 0x0f);

    cpu.execute_next_instruction();
    cpu.execute_next_instruction();
    cpu.execute_next_instruction();
    cpu.execute_next_instruction();
    cpu.execute_next_instruction();
    cpu.execute_next_instruction();
    cpu.execute_next_instruction();
    cpu.execute_next_instruction();
    cpu.execute_next_instruction();
    cpu.execute_next_instruction();

    // auto instruction = InstructionFactory::create(0x00, cpu);
    // instruction->execute(cpu);
    // std::cout << cpu << std::endl;

    // instruction = InstructionFactory::create(0x01, cpu);
    // instruction->execute(cpu);
    // std::cout << cpu << std::endl;


    return 0;
}
