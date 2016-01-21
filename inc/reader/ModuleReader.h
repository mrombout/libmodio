#ifndef LIBMODIO_MODULEREADER_H_H
#define LIBMODIO_MODULEREADER_H_H

#include <fstream>
#include "Module.h"

namespace modio {
    /**
     * \brief Reads in a module and turns its data into a model to be manipulated
     */
    class ModuleReader {
    public:
        virtual ~ModuleReader() {

        }

        /**
         * \brief Reads in a module and turns its data into a model
         *
         * \param in stream to read from
         */
        virtual Module read(std::istream &in) const = 0;
    };
}

#endif //LIBMODIO_MODULEREADER_H_H
