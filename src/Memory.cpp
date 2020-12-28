//
// Created by Joe Landers on 23.05.20.
//

#include "Memory.h"

Memory::Memory() {}

uint32_t linear_address_to_page_index(uint32_t linear_address);
uint32_t linear_address_to_page_offset(uint32_t linear_address);

void
Memory::set_byte(size_t address, uint8_t value, bool print) {
    if (address + 1 > get_size()) {
        throw std::runtime_error("set_byte out of bounds");
    }

    std::cout << "mem set addy ";
    print_quad_in_hex(address);
    std::cout << "to value ";
    print_byte_in_hex(value);
    printf("\n");
    auto page_index = linear_address_to_page_index(address);
    auto page_offset = linear_address_to_page_offset(address);

    if (print) {
        // std::cout << "MEMSET page_index: ";
        // print_quad_in_hex(page_index);
        // std::cout << "page_offset: ";
        // print_quad_in_hex(page_offset);
        std::cout << "MEMSET offset: ";
        print_quad_in_hex(address);
        std::cout << " value: ";
        print_byte_in_hex(value);
        std::cout << std::endl;
    }

    // bytes[address] = value;
    if (pages.find(page_index) != pages.end()) {
        pages[page_index][page_offset] = value;
        // std::cout << "set_byte() in existing page" << std::endl;
    } else {
        pages.insert(std::make_pair(page_index, std::vector<uint8_t>(4096)));
        pages[page_index][page_offset] = value;
        // std::cout << "set_byte() in new page" << std::endl;
    }
}

uint32_t
Memory::get_byte(size_t index, bool print) {
    if (index + 1 > get_size()) {
        throw std::runtime_error("get_byte out of bounds");
    }

    uint8_t value;
    // return bytes.at(address);
    auto page_index = linear_address_to_page_index(index);
    auto page_offset = linear_address_to_page_offset(index);

    if (print) {
        // std::cout << "MEMGET get page_index ";
        // print_quad_in_hex(page_index);
        // std::cout << ", page_offset ";
        // print_quad_in_hex(page_offset);
        std::cout << "MEMGET offset: ";
        print_quad_in_hex(index);
        std::cout << " value: ";
    }

    if (pages.find(page_index) != pages.end()) {
        value = pages[page_index][page_offset];
        print_byte_in_hex(value);
        // std::cout << "get_byte() in existing page" << std::endl;
    } else {
        pages.insert(std::make_pair(page_index, std::vector<uint8_t>(4096)));
        value = pages[page_index][page_offset];
        print_byte_in_hex(value);
        // std::cout << "get_byte() in new page" << std::endl;
    }
    std::cout << std::endl;

    return value;
}

uint32_t
Memory::get_quad(size_t address, bool print) {
    uint32_t value = 0;
    value += get_byte(address, false);
    value += get_byte(address + 1, false) << 8;
    value += get_byte(address + 2, false) << 16;
    value += get_byte(address + 3, false) << 24;

    std::cout << "MEMGET offset: ";
    print_quad_in_hex(address);
    std::cout << "value: ";
    print_quad_in_hex(value);
    std::cout << std::endl;
    return value;
}

uint32_t
Memory::get_dual(size_t address, bool print) {
    uint32_t value = 0;
    value += get_byte(address, false);
    value += get_byte(address + 1, false) << 8;

    std::cout << "MEMGET offset: ";
    print_quad_in_hex(address);
    std::cout << "value: ";
    print_quad_in_hex(value);
    std::cout << std::endl;
    return value;
}

void
Memory::set_quad(size_t start, uint32_t value, bool print) {
    std::cout << "MEMSET offset: ";
    print_quad_in_hex(start);
    std::cout << "value: ";
    print_quad_in_hex(value);
    std::cout << std::endl;

    // if (start + 4 > bytes.size()) {
    //     bytes.resize(start + 4);
    // }

    set_byte(start, value & 0xff, false);
    set_byte(start + 1, (value >> 8) & 0xff, false);
    set_byte(start + 2, (value >> 16) & 0xff, false);
    set_byte(start + 3, (value >> 24) & 0xff, false);
}

void
Memory::set_dual(size_t start, uint32_t value, bool print) {
    std::cout << "MEMSET offset: ";
    print_quad_in_hex(start);
    std::cout << "value: ";
    print_quad_in_hex(value);
    std::cout << std::endl;

    // if (start + 4 > bytes.size()) {
    //     bytes.resize(start + 4);
    // }

    set_byte(start, value & 0xff, false);
    set_byte(start + 1, (value >> 8) & 0xff, false);
}

void
Memory::set_bytes(size_t start, std::string hex_string) {
    std::cout << "MEMSETBS offset: ";
    print_quad_in_hex(start);
    std::cout << "value: " << hex_string << std::endl;
    std::vector<std::string> hexes;
    boost::split(hexes, hex_string, boost::is_any_of(" "));

    // if (start + hexes.size() > bytes.size()) {
    //     bytes.resize(start + hexes.size());
    // }

    size_t i = start;
    for (auto& hex_digit : hexes) {
        std::stringstream ss;
        uint8_t byte = strtol(hex_digit.c_str(), NULL, 16);
        set_byte(i, byte, false);
        ++i;
    }
}

void
Memory::set_bytes(size_t start, std::vector<uint8_t> new_bytes) {
    std::cout << "MEMSETBS offset: ";
    print_quad_in_hex(start);
    std::cout << "value: ";

    // if (start + new_bytes.size() > bytes.size()) {
    //     bytes.resize(start + new_bytes.size());
    // }

    size_t i = start;
    for (auto& byte : new_bytes) {
        print_byte_in_hex(byte);
        printf(" ");
        set_byte(i, byte);
        ++i;
    }
    std::cout << std::endl;
}

uint32_t
linear_address_to_page_index(uint32_t linear_address) {
    return (linear_address >> 12) & 0xfffff;
}

uint32_t
linear_address_to_page_offset(uint32_t linear_address) {
    return linear_address & 0xfff;
}

void
Memory::set_zero_bytes(size_t start, size_t len) {
    // if (start + len > bytes.size()) {
    //     bytes.resize(start + len);
    // }

    for (size_t i = start; i < len; i++) {
        set_byte(i, 0);
    }
}

std::ostream&
operator<<(std::ostream& os, const Memory& memory) {
    os << "Memory:" << std::endl;
    os << "\tsize: " << memory.get_size();
    os << "\n\t";
    auto it = memory.get_pages().begin();
    while(it != memory.get_pages().end()) {
        print_quad_in_hex(it->first);
        print_vector_bytes(it->second);
    }
    return os;
}
