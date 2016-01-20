#ifndef LIBMODIO_MODWRITER_H
#define LIBMODIO_MODWRITER_H

#include "ModuleWriter.h"
#include "Module.h"

namespace modio {
    class ModWriter : public ModuleWriter {
    public:
        virtual void write(const Module &module, std::ostream &out) const;

        void writeSampleHeaders(std::ostream &out, const Module &module) const;
        void writeSampleHeader(std::ostream &out, const Sample &sample) const;

        void writePatterns(std::ostream &out, const Module &module) const;
        void writePattern(std::ostream &out, Pattern &pattern) const;
    };
}

#endif //LIBMODIO_MODWRITER_H
