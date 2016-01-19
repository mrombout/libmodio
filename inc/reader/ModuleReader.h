#ifndef LIBMODIO_MODULEREADER_H_H
#define LIBMODIO_MODULEREADER_H_H

#include <fstream>
#include "Module.h"

namespace modio {
    class ModuleReader {
    public:
        virtual ~ModuleReader() {

        }

        virtual Module read(std::istream &in) const = 0;
    };
}

#endif //LIBMODIO_MODULEREADER_H_H
