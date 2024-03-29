//
// Created by Joe Landers on 23.05.20.
//

#ifndef EXAMPLE_REGISTERLOCATION_H
#define EXAMPLE_REGISTERLOCATION_H

#include "LocationBase.h"
#include "util.h"

class RegisterLocation : public LocationBase {
  public:
    RegisterLocation(Register new_reg);
    ~RegisterLocation(){};
    virtual uint32_t read(CPU& cpu, Width w);
    virtual void write(CPU& cpu, Width w, uint32_t value);

    virtual void print(Width w);

    Register reg;
    Width wid;
};


#endif // EXAMPLE_REGISTERLOCATION_H
