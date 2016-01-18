#ifndef LIBMODIO_MODWRITER_H
#define LIBMODIO_MODWRITER_H

#include "ModuleWriter.h"
#include "Module.h"

namespace modio {
    class ModWriter : public ModuleWriter {
    public:
        virtual void write(const Module &module, std::ostream &os) const;
    };
}

#endif //LIBMODIO_MODWRITER_H
