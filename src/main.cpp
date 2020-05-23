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

    cpu.get_memory().set_bytes(0, "2e 36 0b bb");
    std::cout << cpu << std::endl;

    cpu.get_memory().set_bytes(4, "11 26 33 44");
    std::cout << cpu << std::endl;

    cpu.get_memory().set_zero_bytes(20, 20);
    std::cout << cpu << std::endl;

    cpu.execute_next_instruction();
    cpu.execute_next_instruction();
    cpu.execute_next_instruction();
    cpu.execute_next_instruction();
    cpu.execute_next_instruction();

    auto instruction = InstructionFactory::create(0x00, cpu);
    instruction->execute();
    std::cout << cpu << std::endl;

    instruction = InstructionFactory::create(0x01, cpu);
    instruction->execute();
    std::cout << cpu << std::endl;


    return 0;
}
