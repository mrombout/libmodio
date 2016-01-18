#ifndef LIBMODIO_MODREADER_H
#define LIBMODIO_MODREADER_H

#include "ModuleReader.h"

namespace modio {
    class ModReader : public ModuleReader {
    public:
        virtual void read() const;
    };
}

#endif //LIBMODIO_MODREADER_H
