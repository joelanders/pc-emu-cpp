//
// Created by Joe Landers on 23.05.20.
//

#ifndef EXAMPLE_LOCATIONBASE_H
#define EXAMPLE_LOCATIONBASE_H

#include "mylib.h"
#include "CPU.h"

class LocationBase {
  public:
    LocationBase() = default;
    virtual ~LocationBase() = default;
    virtual uint32_t read(CPU& cpu, Width w) = 0;
    virtual uint32_t write(CPU& cpu, Width w, uint32_t value) = 0;
};




#endif // EXAMPLE_LOCATIONBASE_H
