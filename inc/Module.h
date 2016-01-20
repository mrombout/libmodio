#ifndef LIBMODIO_MODULE_H
#define LIBMODIO_MODULE_H

#include <string>
#include <vector>
#include "Sample.h"
#include "Pattern.h"
#include "Sequence.h"

namespace modio {
    class Module {
    public:
        Module();
        Module(const std::string &name);
        Module(const std::string &name, const std::string &signature);

        const std::string &name() const;
        void setName(const std::string &name);

        const unsigned int length() const;
        void setLength(unsigned int length);

        const std::string &signature() const;
        void setSignature(const std::string &signature);

        const std::vector<Sample> samples() const;
        void setSample(unsigned int index, const Sample &sample);

        const std::vector<Pattern> patterns() const;
        void setPattern(unsigned int index, const Pattern &pattern);

        const Sequence &sequence() const;

        void set(unsigned int orderIndex, unsigned int patternIndex);
        unsigned int get(unsigned int orderIndex);

    private:
        std::string mName;
        std::string mSignature;

        Sequence mSequence;

        std::vector<Sample> mSamples;
        std::vector<Pattern> mPatterns;
    };
}

#endif //LIBMODIO_MODULE_H
