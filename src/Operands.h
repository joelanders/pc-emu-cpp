#ifndef EXAMPLE_OPERANDS_H
#define EXAMPLE_OPERANDS_H

#include <memory>
#include "LocationBase.h"
#include "RegisterLocation.h"
#include "MemoryLocation.h"

class Operands {
    public:
        Operands(std::unique_ptr<LocationBase>, std::unique_ptr<RegisterLocation>);
        void print();

        std::unique_ptr<LocationBase> E();
        std::unique_ptr<RegisterLocation> G();

        std::unique_ptr<LocationBase> e;
        std::unique_ptr<RegisterLocation> g;
};

Operands decode_modrm(CPU& cpu);


#endif // EXAMPLE_OPERANDS_H
