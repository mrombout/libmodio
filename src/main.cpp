#include <iostream>
#include <fstream>

int main() {
    std::ofstream os{"test.mod", std::ios::out | std::ios::binary};

    // (20 bytes) write title
    std::string title{"ABCDEFGHIJKLMNOPQRST"};
    os.write(title.c_str(), title.length());

    // repeated for each sample
    char sampleNames[]{'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '1', '2', '3', '4', '5'};
    for(int i = 0; i < sizeof(sampleNames); ++i) {
        // (22 bytes) write sample 1
        std::string sampleName(22, sampleNames[i]);
        os.write(sampleName.c_str(), sampleName.length());

        // (1 byte) ???
        char sampleUnknown1[]{0x0};
        os.write(sampleUnknown1, sizeof(sampleUnknown1));

        // (1 byte) sample 1 length in words (1 word = 2 bytes)
        char sampleLength[]{0x20};
        os.write(sampleLength, sizeof(sampleLength));

        // (1 byte) ???
        char sampleUnknown2[]{0x0};
        os.write(sampleUnknown2, sizeof(sampleUnknown2));

        // (1 byte) volume of sample (legal are 0..64)
        char sampleVolume[]{0x40};
        os.write(sampleVolume, sizeof(sampleVolume));

        // (2 bytes) start of sample repeat offset
        char sampleRepeatStart[]{0x00, 0x00};
        os.write(sampleRepeatStart, sizeof(sampleRepeatStart));

        // (2 bytes) length of sample repeat in words.
        char sampleRepeatLength[]{0x00, 0x20};
        os.write(sampleRepeatLength, sizeof(sampleRepeatLength));
    }

    // (1 byte) number of song positions (ie. number of patterns played throughout the song). Legal values are 1..128
    char songPositions[]{0x01};
    os.write(songPositions, sizeof(songPositions));

    // (1 byte) Historically set to 127, but can be safely ignored. Noisetracker uses this byte to for restart position
    char historyLesson[]{0x00};
    os.write(historyLesson, sizeof(historyLesson));

    // (128 bytes) Pattern table: patterns to play in each song position (0..127)
    char patternTable[128]{};
    os.write(patternTable, sizeof(patternTable));

    // (4 bytes) signature
    std::string songSignature{"M.K."};
    os.write(songSignature.c_str(), songSignature.length());

    // (1 byte) ???
    char songUnknown[]{0x0};
    os.write(songUnknown, sizeof(songUnknown));

    // data repeated for each pattern
    char pattern[1024]{};
    for(int i = 0; i < 64; ++i) {
        char ch1[]{0xD6, 0x11, 0x00, 0x00};
        char ch2[]{0xBE, 0x12, 0x00, 0x00};
        char ch3[]{0xAA, 0x13, 0x00, 0x00};
        char ch4[]{0xA0, 0x14, 0x00, 0x00};

        os.write(ch1, sizeof(ch1));
        os.write(ch2, sizeof(ch2));
        os.write(ch3, sizeof(ch3));
        os.write(ch4, sizeof(ch4));
    }

    // (1 byte) remove last byte from pattern (???)
    os.seekp(-1, os.cur);

    // data repeated for each sample
    for(int i = 0; i < sizeof(sampleNames); ++i) {
        char sample[64]{};
        std::fill_n(sample, sizeof(sample), i % 2 == 0 ? 0x7F : 0x80);
        os.write(sample, sizeof(sample));
    }

    return 0;
}