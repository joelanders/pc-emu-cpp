#pragma once

#include <cstdint>
#include <vector>

class Addressable {
  public:
    virtual ~Addressable(){};
};

class Memory : public Addressable {
  public:
    Memory();
    virtual ~Memory(){};
    uint32_t get_byte(size_t index) { return bytes.at(index); };
    void set_bytes(size_t start, std::string hex_string);
    size_t get_size() const { return bytes.size(); };
    const std::vector<uint8_t>& get_bytes() const { return bytes; };

  private:
    std::vector<uint8_t> bytes;
};

class Registers : public Addressable {
  public:
    Registers();
    virtual ~Registers(){};
    uint32_t get_eax() const { return eax; }
    uint32_t get_ecx() const { return ecx; }
    uint32_t get_ebx() const { return ebx; }
    uint32_t get_edx() const { return edx; }
    uint32_t get_eip() const { return eip; }
    void inc_eip() { ++eip; }

  private:
    uint32_t eax;
    uint32_t ecx;
    uint32_t ebx;
    uint32_t edx;
    uint32_t eip;
};

class CPU {
  public:
    CPU();
    void execute_next_instruction();
    const Registers& get_registers() const { return registers; };
    const Memory& get_memory() const { return memory; };

    Registers& get_registers() { return registers; };
    Memory& get_memory() { return memory; };

  private:
    Registers registers;
    Memory memory;
};

std::ostream& operator<<(std::ostream& os, CPU const& cpu);
std::ostream& operator<<(std::ostream& os, Memory const& memory);
std::ostream& operator<<(std::ostream& os, Registers const& registers);
