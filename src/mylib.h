#pragma once

#include <cstdint>
#include <map>
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
    void set_byte(size_t address, uint8_t value);
    void set_bytes(size_t start, std::string hex_string);
    void set_zero_bytes(size_t start, size_t len); // XXX how to type-enforce len vs end
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

    void set_byte(size_t address, uint8_t value);
    void set_bytes(size_t start, std::string hex_string);

  private:
    Registers registers;
    Memory memory;
};


std::ostream&
operator<<(std::ostream& os, CPU const& cpu);
std::ostream&
operator<<(std::ostream& os, Memory const& memory);
std::ostream&
operator<<(std::ostream& os, Registers const& registers);

void
print_byte_in_hex(uint8_t byte);
void
print_quad_in_hex(uint32_t quad);


enum Register { Eax, Ecx, Ebx, Edx, Eip, Esp };
enum Width { U8, U16, U32 };

class LocationBase {
  public:
    LocationBase() = default;
    virtual ~LocationBase() = default;
    virtual uint32_t read(CPU& cpu, Width w) = 0;
    virtual uint32_t write(CPU& cpu, Width w, uint32_t value) = 0;
};


class RegisterLocation : public LocationBase {
  public:
    RegisterLocation(Register reg);
    ~RegisterLocation(){};
    virtual uint32_t read(CPU& cpu, Width w);
    virtual uint32_t write(CPU& cpu, Width w, uint32_t value);

  private:
    Register reg;
};


class MemoryLocation : public LocationBase {
  public:
    MemoryLocation(uint32_t address);
    ~MemoryLocation(){};
    virtual uint32_t read(CPU& cpu, Width w);
    virtual uint32_t write(CPU& cpu, Width w, uint32_t value);

  private:
    uint32_t address;
};


// abstract base class
class InstructionBase {
  public:
    InstructionBase() = default;
    virtual ~InstructionBase(){};
    virtual bool execute() = 0;
};


class InstructionFactory {
  public:
    InstructionFactory();
    using InstructionConstructor = std::function<std::unique_ptr<InstructionBase>()>;
    static bool register_opcode(uint8_t opcode, InstructionConstructor);
    static std::unique_ptr<InstructionBase> create(uint8_t);

  private:
    static std::map<uint8_t, InstructionConstructor> instruction_set;
};


class ArithmeticInstruction : public InstructionBase {
  public:
    ArithmeticInstruction(uint8_t opcode, CPU& cpu);
    virtual ~ArithmeticInstruction(){};
    virtual bool execute();

  private:
    uint8_t opcode;
    CPU& cpu;
    bool add(LocationBase& dest, LocationBase& src);
};
