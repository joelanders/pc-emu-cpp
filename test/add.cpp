#include <gtest/gtest.h>
#include "mylib.h"

TEST(Add, reg_reg) {
    CPU cpu;
    std::vector<uint8_t> bytes = { 0x00, 0b11001000 };  //  reg = ecx,  rm = eax
    cpu.set_bytes(0x00, bytes);                         // dest = eax, src = ecx
    cpu.set_register(U8, Eax, 0x10);
    cpu.set_register(U8, Ecx, 0x01);
    cpu.execute_next_instruction();
    EXPECT_EQ(0x11, cpu.get_registers().get_eax());
}

TEST(Add, mem_reg) {
    CPU cpu;
    std::vector<uint8_t> bytes = { 0x01, 0b00010011 };  //  reg = edx,   rm = ebx
    cpu.set_bytes(0x00, bytes);                         // dest = [rm], src = reg
    cpu.set_bytes(300, "01 02 03 04");
    cpu.set_register(U32, Ebx, 300);
    cpu.set_register(U32, Edx, 0x01020304);
    cpu.execute_next_instruction();
    EXPECT_EQ(0x05050505, cpu.get_memory().get_quad(300));
}

TEST(Add, reg_mem_disp) {
    CPU cpu;
    std::vector<uint8_t> bytes = { 0x03, 0b10111110 };  //  reg = edi,  rm = esi
    cpu.set_bytes(0x00, bytes);                         // dest = reg, src = [rm + disp32]
    std::vector<uint8_t> disp32_bytes = { 0xaa, 0x01, 0x00, 0x00 };
    cpu.set_bytes(0x02, disp32_bytes);
    cpu.set_bytes(0x01aa + 300, "02 04 06 08");
    cpu.set_register(U32, Esi, 300);
    cpu.set_register(U32, Edi, 0x01020304);
    cpu.execute_next_instruction();
    EXPECT_EQ(0x09080706, cpu.get_registers().get_edi());
}

TEST(Add, al_imm) {
    CPU cpu;
    std::vector<uint8_t> bytes = { 0x04, 0xe0 };
    cpu.set_bytes(0x00, bytes);
    cpu.set_register(U8, Eax, 0x11);
    cpu.execute_next_instruction();
    EXPECT_EQ(0xf1, cpu.get_registers().get_eax());
}

TEST(Add, eax_imm) {
    CPU cpu;
    std::vector<uint8_t> bytes = { 0x05, 0x11, 0x22, 0x33, 0x44 };
    cpu.set_bytes(0x00, bytes);
    cpu.set_register(U32, Eax, 0x01020304);
    cpu.execute_next_instruction();
    EXPECT_EQ(0x45352515, cpu.get_registers().get_eax());
}
