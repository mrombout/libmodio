#ifndef LIBMODIO_MODREADER_H
#define LIBMODIO_MODREADER_H

#include "ModuleReader.h"

namespace modio {
    class ModReader : public ModuleReader {
    public:
        virtual Module read(std::istream &in) const;

    private:
        std::string readString(std::istream &in, int size) const;
    };
}

#endif //LIBMODIO_MODREADER_H
