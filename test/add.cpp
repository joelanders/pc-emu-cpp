#include "mylib.h"
#include <gtest/gtest.h>

//
// ADD
//

TEST(Add, reg_reg) {
    CPU cpu;
    std::vector<uint8_t> bytes = {0x00, 0b11001000}; //  reg = ecx,  rm = eax
    cpu.set_bytes(0x00, bytes);                      // dest = eax, src = ecx
    cpu.set_register(U8, Al, 0x10);
    cpu.set_register(U8, Cl, 0x01);
    cpu.execute_next_instruction();
    EXPECT_EQ(0x11, cpu.get_registers().get_eax());
}

TEST(Add, mem_reg) {
    CPU cpu;
    std::vector<uint8_t> bytes = {0x01, 0b00010011}; //  reg = edx,   rm = ebx
    cpu.set_bytes(0x00, bytes);                      // dest = [rm], src = reg
    cpu.set_bytes(300, "01 02 03 04");
    cpu.set_register(U32, Ebx, 300);
    cpu.set_register(U32, Edx, 0x01020304);
    cpu.execute_next_instruction();
    EXPECT_EQ(0x05050505, cpu.get_memory().get_quad(300));
}

TEST(Add, reg_mem_disp) {
    CPU cpu;
    std::vector<uint8_t> bytes = {0x03, 0b10111110}; //  reg = edi,  rm = esi
    cpu.set_bytes(0x00, bytes);                      // dest = reg, src = [rm + disp32]
    std::vector<uint8_t> disp32_bytes = {0xaa, 0x01, 0x00, 0x00};
    cpu.set_bytes(0x02, disp32_bytes);
    cpu.set_bytes(0x01aa + 300, "02 04 06 08");
    cpu.set_register(U32, Esi, 300);
    cpu.set_register(U32, Edi, 0x01020304);
    cpu.execute_next_instruction();
    EXPECT_EQ(0x09080706, cpu.get_registers().get_edi());
}

TEST(Add, al_imm) {
    CPU cpu;
    std::vector<uint8_t> bytes = {0x04, 0xe0};
    cpu.set_bytes(0x00, bytes);
    cpu.set_register(U8, Al, 0x11);
    cpu.execute_next_instruction();
    EXPECT_EQ(0xf1, cpu.get_registers().get_eax());
}

TEST(Add, eax_imm) {
    CPU cpu;
    std::vector<uint8_t> bytes = {0x05, 0x11, 0x22, 0x33, 0x44};
    cpu.set_bytes(0x00, bytes);
    cpu.set_register(U32, Eax, 0x01020304);
    cpu.execute_next_instruction();
    EXPECT_EQ(0x45352515, cpu.get_registers().get_eax());
}

//
// PUSH / POP
//

TEST(Push, es) {
    CPU cpu;
    cpu.current_value_size = U32;
    std::vector<uint8_t> bytes = {0x06};
    cpu.set_bytes(0x00, bytes);
    cpu.set_register(U32, Esp, 0x11);
    cpu.set_register(U32, Es, 0x69707172);
    cpu.execute_next_instruction();
    EXPECT_EQ(0x69707172, cpu.get_memory().get_quad(0x0d));
    EXPECT_EQ(0x0d, cpu.get_registers().get_esp());
}

TEST(Pop, es) {
    CPU cpu;
    cpu.current_value_size = U32;
    std::vector<uint8_t> bytes = {0x07};
    cpu.set_bytes(0x00, bytes);
    cpu.set_register(U16, Esp, 0x20);
    cpu.set_byte(0x20, 0x99);
    cpu.execute_next_instruction();
    EXPECT_EQ(0x99, cpu.get_registers().get_es());
    EXPECT_EQ(0x24, cpu.get_registers().get_esp());
}

//
// OR
//

TEST(Or, reg_reg) {
    CPU cpu;
    std::vector<uint8_t> bytes = {0x08, 0b11001000}; //  reg = ecx,  rm = eax
    cpu.set_bytes(0x00, bytes);                      // dest = eax, src = ecx
    cpu.set_register(U8, Al, 0b00010001);
    cpu.set_register(U8, Cl, 0b10001000);
    cpu.execute_next_instruction();
    EXPECT_EQ(0b10011001, cpu.get_registers().get_eax());
}

TEST(Or, mem_reg) {
    CPU cpu;
    std::vector<uint8_t> bytes = {0x09, 0b00010011}; //  reg = edx,   rm = ebx
    cpu.set_bytes(0x00, bytes);                      // dest = [rm], src = reg
    cpu.set_bytes(300, "01 02 03 04");
    cpu.set_register(U32, Ebx, 300);
    cpu.set_register(U32, Edx, 0x01020304);
    cpu.execute_next_instruction();
    EXPECT_EQ(0x05030305, cpu.get_memory().get_quad(300));
}

TEST(Or, reg_mem_disp) {
    CPU cpu;
    std::vector<uint8_t> bytes = {0x0b, 0b10111110}; //  reg = edi,  rm = esi
    cpu.set_bytes(0x00, bytes);                      // dest = reg, src = [rm + disp32]
    std::vector<uint8_t> disp32_bytes = {0xaa, 0x01, 0x00, 0x00};
    cpu.set_bytes(0x02, disp32_bytes);
    cpu.set_bytes(0x01aa + 300, "02 04 06 08");
    cpu.set_register(U32, Esi, 300);
    cpu.set_register(U32, Edi, 0x01020304);
    cpu.execute_next_instruction();
    EXPECT_EQ(0x09060706, cpu.get_registers().get_edi());
}

TEST(Or, al_imm) {
    CPU cpu;
    std::vector<uint8_t> bytes = {0x0c, 0xe0};
    cpu.set_bytes(0x00, bytes);
    cpu.set_register(U8, Al, 0x11);
    cpu.execute_next_instruction();
    EXPECT_EQ(0xf1, cpu.get_registers().get_eax());
}

TEST(Or, eax_imm) {
    CPU cpu;
    std::vector<uint8_t> bytes = {0x0d, 0x11, 0x22, 0x33, 0x44};
    cpu.set_bytes(0x00, bytes);
    cpu.set_register(U32, Eax, 0x01020304);
    cpu.execute_next_instruction();
    EXPECT_EQ(0x45332315, cpu.get_registers().get_eax());
}

//
// PUSH / POP
//

TEST(Push, cs) {
    CPU cpu;
    cpu.current_value_size = U16;
    std::vector<uint8_t> bytes = {0x0e};
    cpu.set_bytes(0x00, bytes);
    cpu.set_register(U16, Esp, 0x11);
    cpu.set_register(U16, Cs, 0x69);
    cpu.execute_next_instruction();
    EXPECT_EQ(0x69, cpu.get_memory().get_byte(0x0f, true));
    EXPECT_EQ(0x0f, cpu.get_registers().get_esp());
}

TEST(Pop, cs) {
    CPU cpu;
    cpu.current_value_size = U16;
    std::vector<uint8_t> bytes = {0x0f};
    cpu.set_bytes(0x00, bytes);
    cpu.set_register(U16, Esp, 0x20);
    cpu.set_byte(0x20, 0x99);
    cpu.execute_next_instruction();
    EXPECT_EQ(0x99, cpu.get_registers().get_cs());
    EXPECT_EQ(0x22, cpu.get_registers().get_esp());
}

TEST(Push, eax16) {
    CPU cpu;
    cpu.current_value_size = U16;
    std::vector<uint8_t> bytes = {0x50};
    cpu.set_bytes(0x00, bytes);
    cpu.set_register(U16, Esp, 0x11);
    cpu.set_register(U16, Eax, 0x6970);
    cpu.execute_next_instruction();
    EXPECT_EQ(0x70, cpu.get_memory().get_byte(0x0f, true));
    EXPECT_EQ(0x0f, cpu.get_registers().get_esp());
}

TEST(Pop, eax16) {
    CPU cpu;
    cpu.current_value_size = U16;
    std::vector<uint8_t> bytes = {0x58};
    cpu.set_bytes(0x00, bytes);
    cpu.set_register(U16, Esp, 0x20);
    cpu.set_byte(0x20, 0x99);
    cpu.execute_next_instruction();
    EXPECT_EQ(0x99, cpu.get_registers().get_eax());
    EXPECT_EQ(0x22, cpu.get_registers().get_esp());
}

TEST(Push, eax32) {
    CPU cpu;
    cpu.current_value_size = U32;
    std::vector<uint8_t> bytes = {0x50};
    cpu.set_bytes(0x00, bytes);
    cpu.set_register(U32, Esp, 0x11);
    cpu.set_register(U32, Eax, 0x6970);
    cpu.execute_next_instruction();
    EXPECT_EQ(0x70, cpu.get_memory().get_byte(0x0d, true));
    EXPECT_EQ(0x0d, cpu.get_registers().get_esp());
}

TEST(Pop, eax32) {
    CPU cpu;
    cpu.current_value_size = U32;
    std::vector<uint8_t> bytes = {0x58};
    cpu.set_bytes(0x00, bytes);
    cpu.set_register(U32, Esp, 0x20);
    cpu.set_byte(0x20, 0x99);
    cpu.execute_next_instruction();
    EXPECT_EQ(0x99, cpu.get_registers().get_eax());
    EXPECT_EQ(0x24, cpu.get_registers().get_esp());
}

//
// Jcc
//

TEST(Jcc, JO) {
    CPU cpu;
    std::vector<uint8_t> bytes = {0x70, 0x10};
    cpu.set_bytes(0x100, bytes);
    cpu.get_registers().set_eip(0x100);
    cpu.get_registers().set_of(true);
    cpu.execute_next_instruction();
    EXPECT_EQ(0x112, cpu.get_registers().get_eip());
}

TEST(Jcc, JNO) {
    CPU cpu;
    std::vector<uint8_t> bytes = {0x71, 0xf0};
    cpu.set_bytes(0x200, bytes);
    cpu.get_registers().set_eip(0x200);
    cpu.get_registers().set_of(true);
    cpu.execute_next_instruction();
    EXPECT_EQ(0x202, cpu.get_registers().get_eip());
}

TEST(Jcc, JB) {
    CPU cpu;
    std::vector<uint8_t> bytes = {0x72, 0xf0};
    cpu.set_bytes(0x200, bytes);
    cpu.get_registers().set_eip(0x200);
    cpu.get_registers().set_cf(true);
    cpu.execute_next_instruction();
    EXPECT_EQ(0x1f2, cpu.get_registers().get_eip());
}

//
// MOV
//
TEST(Mov, reg_reg) {
    CPU cpu;
    std::vector<uint8_t> bytes = {0x88, 0b11001000}; //  reg = ecx,  rm = eax
    cpu.set_bytes(0x00, bytes);                      // dest = eax, src = ecx
    cpu.set_register(U32, Ecx, 0x69);
    cpu.execute_next_instruction();
    EXPECT_EQ(0x69, cpu.get_registers().get_eax());
}

TEST(Mov, mem_reg) {
    CPU cpu;
    std::vector<uint8_t> bytes = {0x89, 0b00010011}; //  reg = edx,   rm = ebx
    cpu.set_bytes(0x00, bytes);                      // dest = [rm], src = reg
    cpu.set_register(U32, Ebx, 300);
    cpu.set_register(U32, Edx, 0x01020304);
    cpu.execute_next_instruction();
    EXPECT_EQ(0x01020304, cpu.get_memory().get_quad(300));
}

TEST(Mov, reg_mem) {
    CPU cpu;
    std::vector<uint8_t> bytes = {0x8b, 0b00010011}; //  reg = edx,   rm = ebx
    cpu.set_bytes(0x00, bytes);                      // dest = reg, src = [rm]
    cpu.set_register(U32, Ebx, 0x10f0);
    std::vector<uint8_t> bytes2 = {0x69, 0x70, 0x71, 0x72};
    cpu.set_bytes(0x10f0, bytes2);
    cpu.execute_next_instruction();
    EXPECT_EQ(0x72717069, cpu.get_memory().get_quad(0x10f0));
}

