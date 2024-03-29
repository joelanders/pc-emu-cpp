#ifndef EXAMPLE_OPERANDS_H
#define EXAMPLE_OPERANDS_H

#include "LocationBase.h"
#include "MemoryLocation.h"
#include "RegisterLocation.h"
#include <memory>

class Operands {
  public:
    Operands(std::unique_ptr<LocationBase>, std::unique_ptr<RegisterLocation>);
    void print(Width w);

    std::unique_ptr<LocationBase> E();
    std::unique_ptr<RegisterLocation> G();

    std::unique_ptr<LocationBase> e;
    std::unique_ptr<RegisterLocation> g;
};

Operands
decode_modrm(CPU& cpu, Width w);


#endif // EXAMPLE_OPERANDS_H
