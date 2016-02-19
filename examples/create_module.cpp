#include <random>
#include <fstream>
#include <iostream>
#include "writer/ModWriter.h"
#include "Module.h"

/**
 * \brief Creates a new module from scratch
 *
 * This example demonstrates how to create a new module file from scratch and
 * than writing that module to a file. Everything should be rather
 * straightforward, however for clarity's sake the code is also commented to
 * further improve the understanding of what is happening exactly.
 *
 * It is strongly recommended not to listen to the resulting .mod file this
 * code produces. Seriously, don't. Opening it up in a tracker is going to be
 * fine though.
 */

int main(int argc, char *argv[]) {
    if(argc < 2) {
        std::cout << "usage: create_module <filename>" << std::endl;
        return -1;
    }

    modio::Module module{"Beclouded Rhapsodist", "M.K."};
    module.setLength(2);

    //-------------------------------
    // SAMPLES
    //-------------------------------

    // create sine sample
    const int SINE_SAMPLE{1};
    std::vector<unsigned char> sineWave {
            0xFF, 0xF3, 0xE6, 0xDA, 0xCE, 0xC3, 0xB8, 0xAE, 0xA5, 0x9D, 0x95, 0x8F, 0x8A, 0x85, 0x82, 0x81,
            0x80, 0x81, 0x82, 0x85, 0x8A, 0x8F, 0x95, 0x9D, 0xA5, 0xAE, 0xB8, 0xC3, 0xCE, 0xDA, 0xE6, 0xF3,
            0xFF, 0x0C, 0x18, 0x24, 0x30, 0x3B, 0x46, 0x50, 0x5A, 0x62, 0x69, 0x70, 0x75, 0x79, 0x7D, 0x7E,
            0x7F, 0x7E, 0x7D, 0x79, 0x75, 0x70, 0x69, 0x62, 0x5A, 0x50, 0x46, 0x3B, 0x30, 0x24, 0x18, 0x0C
    };
    auto sineSample = modio::Sample("Sine", 64, 0, 32, sineWave);
    module.setSample(SINE_SAMPLE, sineSample);

    // create noise sample
    const int NOISE_SAMPLE{2};
    const int NOISE_SAMPLE_SIZE{4096};
    std::vector<unsigned char> noiseData;
    std::mt19937 rng_engine(0);
    std::uniform_int_distribution<int> dist(-127, 127);
    for(int i = 0; i < NOISE_SAMPLE_SIZE; ++i)
        noiseData.push_back(dist(rng_engine));
    auto noiseSample = modio::Sample("Noise", 64, 0, NOISE_SAMPLE_SIZE / 2, noiseData);
    module.setSample(NOISE_SAMPLE, noiseSample);

    //-------------------------------
    // PATTERNS
    //-------------------------------

    // create pattern
    modio::Pattern pattern;

    // create bass track (channel 1)
    unsigned int bassPattern[4]{modio::C3, 0, modio::C2, 0};
    for(unsigned int i = 0; i < 64; ++i) {
        pattern.set(modio::CHANNEL1, i, bassPattern[i % 4], SINE_SAMPLE, 0);
    }

    // create noise (channel 2)
    for(unsigned int i = 0; i < 64; ++i) {
        pattern.set(modio::CHANNEL2, i, (i == 0) ? modio::C3 : 0, NOISE_SAMPLE, 0xA0F);
    }

    // create melody (channel 3)
    unsigned int melodyPattern[8]{ modio::C3, modio::D3, modio::E3, modio::F3, modio::G3, modio::A3, modio::B3, modio::C3 };
    for(unsigned int i = 0; i < 64; ++i) {
        pattern.set(modio::CHANNEL3, i, melodyPattern[i % 8], SINE_SAMPLE, 0);
    }

    // set pattern
    module.setPattern(0, pattern);

    // create another pattern
    modio::Pattern pattern2{pattern};

    pattern2.clear(modio::CHANNEL3);

    module.setPattern(1, pattern2);

    //-------------------------------
    // SEQUENCE
    //-------------------------------

    // set index 0 and 1 in sequence to pattern 0
    module.set(0, 0);
    module.set(1, 1);

    //-------------------------------
    // WRITE
    //-------------------------------
    std::ofstream out{argv[1]};
    modio::ModWriter writer;
    writer.write(module, out);
}