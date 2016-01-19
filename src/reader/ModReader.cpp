#include <fstream>
#include "Pattern.h"
#include "reader/ModReader.h"

namespace modio {
    Module ModReader::read(std::istream &in) const {
        std::ios::iostate state = in.exceptions();
        in.exceptions(std::istream::failbit | std::istream::badbit); // TODO: Is it okay to modify their stream like that?

        Module module;

        // read title
        std::string name{readString(in, 20)};
        module.setName(name);

        // read samples
        // TODO: Can we assume 31 samples? Some .mod files might allow less (according to http://www.aes.id.au/modformat.html) (1-15)
        for(int i = 0; i < 31; ++i) {
            Sample sample;

            // (22 bytes) read sample name
            char sampleName[22];
            in.read(sampleName, sizeof(sampleName));
            sample.setName(sampleName);

            // (2 bytes) read sample length in words (1 word = 2 bytes)
            unsigned int sampleLength = (in.get() << 8) | in.get();
            sample.resize(sampleLength);

            // (1 byte) finetune
            in.seekg(1, in.cur);

            // (1 byte) read sample volume
            unsigned int sampleVolume = in.get();
            sample.setVolume(sampleVolume);

            // (2 bytes) read repeat start
            unsigned int sampleRepeatStart = (in.get() << 8) | in.get();
            sample.setRepeatStart(sampleRepeatStart);

            // (2 bytes) read repeat length
            unsigned int sampleRepeatLength = (in.get() << 8) | in.get();
            sample.setRepeatLength(sampleRepeatLength);

            module.setSample(i, sample);
        }

        // (1 byte) read number of song positions
        unsigned int songPositions = in.get();
        module.setLength(songPositions);

        // (1 byte) differs from tracker to tracker, traditionally $78 in SoundTracker
        in.seekg(1, in.cur);

        // (128 bytes) read pattern table
        char patternTable[128];
        in.read(patternTable, sizeof(patternTable));
        int highestPatternIndex = 1;

        for(unsigned int i = 0; i < songPositions; ++i) {
            module.set(i, static_cast<unsigned int>(patternTable[i]));
        }

        // (4 bytes) read signature
        char signature[5];
        in.read(signature, sizeof(signature) - 1);
        signature[sizeof(signature) - 1] = '\0';
        module.setSignature(signature);

        // read patterns
        unsigned int channelCount = 4;
        for(unsigned int i = 0; i < highestPatternIndex; ++i) {
            Pattern pattern(channelCount);

            for(unsigned int j = 0; j < channelCount; ++j) { // each channel
                for(unsigned int k = 0; k < 64; ++k) { // each division
                    uint32_t cell = in.get() << 24 | in.get() << 16 | in.get() << 8 | in.get();

                    unsigned int periodData = (cell & 0x0FFF0000) >> 20;
                    Period period{periodData};

                    unsigned int samplePart1  = (cell & 0xF0000000) >> 28;
                    unsigned int samplePart2  = (cell & 0x0000F000) >> 12;
                    unsigned int sampleNumber = (samplePart1 << 4) | samplePart2;

                    unsigned int effectData = (cell & 0x00000FFF);
                    Effect effect(effectData);

                    pattern.set(j, k, period, sampleNumber, effect);
                }
            }

            module.setPattern(i, pattern);
        }

        // read samples
        for(const Sample &sample : module.samples()) {
            char sampleData[sample.length()];
            in.read(sampleData, sizeof(sampleData));
        }

        in.exceptions(state);
        return module;
    }

    std::string ModReader::readString(std::istream &in, int size) const {
        char buffer[size + 1];
        in.read(buffer, size);
        buffer[size] = '\0';

        return std::string(buffer);
    }
}
