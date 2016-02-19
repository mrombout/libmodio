#include <iterator>
#include <c++/iostream>
#include "writer/ModWriter.h"

namespace modio {
    void ModWriter::write(const Module &module, std::ostream &out) const {
        std::ios::iostate state = out.exceptions();
        out.exceptions(std::ostream::failbit | std::ostream::badbit);

        // (20 bytes) write module name
        std::string moduleName{module.name()};
        moduleName.append(20 - moduleName.size(), '\0');
        out.write(moduleName.c_str(), 20);

        // (n * 30 bytes) write sample headers
        writeSampleHeaders(out, module);

        // (1 byte) write number of song positions
        char songPositions{static_cast<char>(module.length())};
        out.put(songPositions);

        // (1 byte) differs from tracker to tracker, traditionally $78 in SoundTracker
        out.put(0x00);

        // (128 bytes) write pattern table
        const std::vector<unsigned int> order{module.sequence().order()};
        for(unsigned int i = 0; i < order.size(); ++i)
            out.put(static_cast<char>(order.at(i)));

        // (4 bytes) write signature
        std::string signature{module.signature()};
        signature.append(4 - signature.size(), '\0');
        out.write(signature.c_str(), signature.size());

        // (n * 1024 bytes) write patterns
        writePatterns(out, module);

        // (n * x ) write sample data
        for(const Sample &sample : module.samples()) {
            auto sampleData = sample.data();
            unsigned int sampleLength = sample.length() * 2;

            for(int i = 0 ; i < sampleLength; ++i)
                out.put(sampleData[i]);
        }

        out.exceptions(state);
    }

    void ModWriter::writeSampleHeaders(std::ostream &out, const Module &module) const {
        for(const Sample &sample : module.samples()) {
            writeSampleHeader(out, sample);
        }
    }

    void ModWriter::writeSampleHeader(std::ostream &out, const Sample &sample) const {
        // (22 bytes) write sample name
        std::string sampleName{sample.name()};
        sampleName.append(22 - sampleName.size(), '\0');
        out.write(sampleName.c_str(), sampleName.length());

        // (2 bytes) write sample length in words
        unsigned int sampleLength{sample.length()};
        out.put(static_cast<char>(sampleLength >> 8));
        out.put(static_cast<char>(sampleLength));

        // (1 byte) write finetune
        out.put(0x00);

        // (1 byte) write sample volume
        unsigned int sampleVolume{sample.volume()};
        out.put(static_cast<char>(sampleVolume));

        // (2 bytes) write repeat start
        unsigned int sampleRepeatStart(sample.repeatStart());
        out.put(static_cast<char>(sampleRepeatStart >> 8));
        out.put(static_cast<char>(sampleRepeatStart));

        // (2 bytes) write repeat length
        unsigned int sampleRepeatLength(sample.repeatLength());
        out.put(static_cast<char>(sampleRepeatLength >> 8));
        out.put(static_cast<char>(sampleRepeatLength));
    }

    void ModWriter::writePatterns(std::ostream &out, const Module &module) const {
        auto patterns = module.patterns();
        for(unsigned int i = 0; i < patterns.size(); ++i) {
            writePattern(out, patterns.at(i));
        }
    }

    void ModWriter::writePattern(std::ostream &out, Pattern &pattern) const {
        for(unsigned int divisionIndex = 0; divisionIndex < 64; ++divisionIndex) {
            for(unsigned int channelIndex = 0; channelIndex < pattern.numChannels(); ++channelIndex) {
                const Division &division = pattern.get(channelIndex, divisionIndex);

                unsigned int cell = 0;

                // sample index (part one)
                unsigned int sampleIndex = division.sampleIndex();
                unsigned int sampleIndexPart1 = (sampleIndex & 0xF0) >> 4;
                unsigned int sampleIndexPart2 = (sampleIndex & 0x0F);

                cell |= sampleIndexPart1 << 28;

                // period
                unsigned int periodData = division.period().period();
                cell |= periodData << 16;

                // sample index (part two)
                cell |= sampleIndexPart2 << 12;

                // effect
                unsigned int effectData = division.effect().raw();
                cell |= effectData;

                // (4 bytes) writes cell
                out.put(static_cast<char>(cell >> 24));
                out.put(static_cast<char>(cell >> 16));
                out.put(static_cast<char>(cell >> 8));
                out.put(static_cast<char>(cell));
            }
        }
    }
}
