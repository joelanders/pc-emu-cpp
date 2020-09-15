//
// Created by Joe Landers on 23.05.20.
//

#ifndef EXAMPLE_MEMORY_H
#define EXAMPLE_MEMORY_H

#include "util.h"


class Memory {
  public:
    Memory();
    virtual ~Memory(){};

    uint32_t get_byte(size_t index, bool print);
    void set_byte(size_t address, uint8_t value, bool print=true);

    uint32_t get_quad(size_t index, bool print=true);
    void set_quad(size_t address, uint32_t value, bool print=true);

    void set_bytes(size_t start, std::string hex_string);
    void set_bytes(size_t start, std::vector<uint8_t> new_bytes);
    void set_zero_bytes(size_t start, size_t len); // XXX how to type-enforce len vs end
    size_t get_size() const { return UINT32_MAX; }
    const std::map<uint32_t, std::vector<uint8_t>>& get_pages() const { return pages; };
    // void set_size(uint32_t mem_size) { bytes.resize(mem_size); };

  private:
    // std::vector<uint8_t> bytes;
    std::map<uint32_t, std::vector<uint8_t>> pages;
};

std::ostream&
operator<<(std::ostream& os, Memory const& memory);

uint32_t linear_address_to_page_index(uint32_t linear_address);
uint32_t linear_address_to_page_offset(uint32_t linear_address);

#endif // EXAMPLE_MEMORY_H
