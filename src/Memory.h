//
// Created by Joe Landers on 23.05.20.
//

#ifndef EXAMPLE_MEMORY_H
#define EXAMPLE_MEMORY_H

#include "mylib.h"
#include "Addressable.h"


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

std::ostream&
operator<<(std::ostream& os, Memory const& memory);



#endif // EXAMPLE_MEMORY_H
