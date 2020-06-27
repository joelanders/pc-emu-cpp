//
// Created by Joe Landers on 23.05.20.
//

#ifndef EXAMPLE_MEMORYLOCATION_H
#define EXAMPLE_MEMORYLOCATION_H

#include "LocationBase.h"
#include "mylib.h"

class MemoryLocation : public LocationBase {
  public:
    MemoryLocation(uint32_t address);
    ~MemoryLocation(){};
    virtual uint32_t read(CPU& cpu, Width w);
    virtual bool write(CPU& cpu, Width w, uint32_t value);

    virtual void print();

  private:
    uint32_t address;
};


#endif // EXAMPLE_MEMORYLOCATION_H
