//
// Created by Joe Landers on 23.05.20.
//

#ifndef EXAMPLE_LOCATIONBASE_H
#define EXAMPLE_LOCATIONBASE_H

#include "CPU.h"
#include "util.h"

class LocationBase {
  public:
    LocationBase() = default;
    virtual ~LocationBase() = default;
    virtual uint32_t read(CPU& cpu, Width w) = 0;
    virtual void write(CPU& cpu, Width w, uint32_t value) = 0;

    virtual void print(Width w) = 0;
};


#endif // EXAMPLE_LOCATIONBASE_H
