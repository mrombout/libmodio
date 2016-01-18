#ifndef LIBMODIO_MODULEWRITER_H
#define LIBMODIO_MODULEWRITER_H

#include <ostream>
#include "Module.h"

namespace modio {
    class ModuleWriter {
    public:
        virtual ~ModuleWriter() {

        }

        virtual void write(const Module &module, std::ostream &os) const = 0;
    };
}

#endif //LIBMODIO_MODULEWRITER_H
