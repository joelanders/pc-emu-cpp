#include <cstdio>
#include <iostream>

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

    std::cout << "HELLO FUCK" << std::endl;

    InstructionFactory::register_opcode(
        0x00, [&cpu]() mutable { return std::make_unique<ArithmeticInstruction>(0x00, cpu); });

    std::cout << "HELLO FUCK 222" << std::endl;

    auto instruction = InstructionFactory::create(0x00);
    std::cout << "HELLO FUCK 3333" << std::endl;
    instruction->execute();
    std::cout << "HELLO FUCK 44444" << std::endl;
    std::cout << cpu << std::endl;


    return 0;
}
