#ifndef LIBMODIO_MODREADER_H
#define LIBMODIO_MODREADER_H

#include "ModuleReader.h"

namespace modio {
    class ModReader : public ModuleReader {
    public:
        virtual Module read(std::istream &in) const;

    private:
        void readSampleHeaders(std::istream &in, Module &module) const;
        void readSampleHeader(std::istream &in, Sample &sample) const;

        void readPatterns(std::istream &in, Module &module, int numPatterns) const;
        void readPattern(std::istream &in, Pattern &pattern, unsigned int channelCount) const;

        std::string readString(std::istream &in, int size) const;
        unsigned int readBigEndian(std::istream &in, int size) const;
    };
}

#endif //LIBMODIO_MODREADER_H
