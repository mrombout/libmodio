#include <fstream>
#include "Pattern.h"
#include "reader/ModReader.h"

namespace modio {
    Module ModReader::read(std::istream &in) const {
        std::ios::iostate state = in.exceptions();
        in.exceptions(std::istream::failbit | std::istream::badbit); // TODO: Is it okay to modify their stream like that?

        Module module;

        // (20 bytes) read module name
        std::string name{readString(in, 20)};
        module.setName(name);

        // (n * 30 bytes) read sample headers
        readSampleHeaders(in, module);

        // (1 byte) read number of song positions
        unsigned int songPositions = in.get();
        module.setLength(songPositions);

        // (1 byte) differs from tracker to tracker, traditionally $78 in SoundTracker
        in.seekg(1, in.cur);

        // (128 bytes) read pattern table
        char patternTable[128];
        in.read(patternTable, sizeof(patternTable));

        int highestPatternIndex = 0;
        for(unsigned int i = 0; i < sizeof(patternTable); ++i) {
            if(i < songPositions)
                module.set(i, static_cast<unsigned int>(patternTable[i]));
            if(patternTable[i] > highestPatternIndex)
                highestPatternIndex = patternTable[i];
        }

        // (4 bytes) read signature
        std::string signature{readString(in, 4)};
        module.setSignature(signature);

        // (n * 1024 bytes) read patterns
        readPatterns(in, module, highestPatternIndex + 1);

        // (n * x) read sample data
        for(const Sample &sample : module.samples()) {
            if(sample.length())
                continue;

            char sampleData[sample.length()];
            in.read(sampleData, sizeof(sampleData));
        }

        in.exceptions(state);
        return module;
    }

    void ModReader::readSampleHeaders(std::istream &in, Module &module) const {
        // TODO: Determine number of samples by signature type
        for(unsigned int i = 1; i <= 31; ++i) {
            Sample sample;

            readSampleHeader(in, sample);

            module.setSample(i, sample);
        }
    }

    void ModReader::readSampleHeader(std::istream &in, Sample &sample) const {
        // (22 bytes) read sample name
        std::string sampleName{readString(in, 22)};
        sample.setName(sampleName);

        // (2 bytes) read sample length in words (1 word = 2 bytes)
        unsigned int sampleLength{readBigEndian(in, 2)};
        sample.resize(sampleLength);

        // (1 byte) read finetune
        in.seekg(1, in.cur);

        // (1 byte) read sample volume
        unsigned int sampleVolume = in.get();
        sample.setVolume(sampleVolume);

        // (2 bytes) read repeat start
        unsigned int sampleRepeatStart{readBigEndian(in, 2)};
        sample.setRepeatStart(sampleRepeatStart);

        // (2 bytes) read repeat length
        unsigned int sampleRepeatLength{readBigEndian(in, 2)};
        sample.setRepeatLength(sampleRepeatLength);
    }

    void ModReader::readPatterns(std::istream &in, Module &module, int numPatterns) const {
        // TODO: Determine channel count by signature/configuration
        unsigned int channelCount = 4;
        for(unsigned int i = 0; i < numPatterns; ++i) {
            Pattern pattern(channelCount);

            readPattern(in, pattern, channelCount);

            module.setPattern(i, pattern);
        }
    }

    void ModReader::readPattern(std::istream &in, Pattern &pattern, unsigned int channelCount) const {
        for(unsigned int j = 0; j < 64; ++j) {
            for(unsigned int i = 0; i < channelCount; ++i) {
                uint32_t cell = readBigEndian(in, 4);

                unsigned int periodData = (cell & 0x0FFF0000) >> 20;
                Period period{periodData};

                unsigned int samplePart1  = (cell & 0xF0000000) >> 28;
                unsigned int samplePart2  = (cell & 0x0000F000) >> 12;
                unsigned int sampleNumber = (samplePart1 << 4) | samplePart2;

                unsigned int effectData = (cell & 0x00000FFF);
                Effect effect(effectData);

                pattern.set(i, j, period, sampleNumber, effect);
            }
        }
    }

    std::string ModReader::readString(std::istream &in, int size) const {
        char buffer[size + 1];
        in.read(buffer, size);
        buffer[size] = '\0';

        return std::string(buffer);
    }

    unsigned int ModReader::readBigEndian(std::istream &in, int bytes) const {
        unsigned int result = 0;

        for(int i = bytes -1; i >= 0; --i)
           result |= in.get() << (i * 8);

        return result;
    }
}
