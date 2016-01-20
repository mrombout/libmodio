#include "gtest/gtest.h"
#include "writer/ModWriter.h"

class ModWriterTest : public ::testing::Test {
protected:
    modio::ModWriter moduleWriter;
};

TEST_F(ModWriterTest, write_FullName__WritesFullName) {
    // arrange
    modio::Module module{"ABCDEFGHIJKLMNOPQRST"};

    // act
    std::stringstream oss;
    moduleWriter.write(module, oss);

    // assert
    oss.seekg(0, oss.beg);

    char buffer[21];
    oss.read(buffer, sizeof(buffer) - 1);
    std::string moduleName{buffer};

    EXPECT_EQ("ABCDEFGHIJKLMNOPQRST", moduleName);
}

TEST_F(ModWriterTest, write_HalfName__WritesHalfNameAndNullPads) {
    // arrange
    modio::Module module{"ABCDEFGHIJ"};

    // act
    std::stringstream oss;
    moduleWriter.write(module, oss);

    // assert
    oss.seekg(0, oss.beg);

    char buffer[20];
    oss.read(buffer, sizeof(buffer));

    for(int i = 0; i < sizeof(buffer); ++i) {
        if(i < module.name().size())
            EXPECT_EQ('A' + i, buffer[i]);
    }
}

TEST_F(ModWriterTest, write_NoSamples_WritesMaxSampleHeaders) {
    // arrange
    modio::Module module;

    // act
    std::stringstream oss;
    moduleWriter.write(module, oss);

    // assert
    oss.seekg(20, oss.beg);

    for(int i = 0; i < 31; ++i) {
        oss.seekg(22, oss.cur);

        char emptySample[8]{0x0, 0x0, 0x0, 0x40, 0x0, 0x0, 0x0, 0x0};
        for(int j = 0; j < sizeof(emptySample); ++j) {
            EXPECT_EQ(emptySample[j], oss.get());
        }
    }
}

TEST_F(ModWriterTest, write_OneSample_WritesMaxSampleHeaders) {
    // arrange
    modio::Module module;

    modio::Sample sample{"SAMPLE01", 64, 0, 32};
    sample.setData(std::vector<unsigned char>(32, 0xFF));

    module.setSample(0, sample);

    // act
    std::stringstream oss;
    moduleWriter.write(module, oss);

    // assert
    oss.seekg(20, oss.beg);

    for(int i = 0; i < 31; ++i) {
        oss.seekg(22, oss.cur);

        char emptySample[8]{0x00, 0x10, 0x00, 0x40, 0x00, 0x00, 0x00, 0x20};
        for(int j = 0; j < sizeof(emptySample); ++j) {
            if (i == 0) {
                EXPECT_EQ(emptySample[j], oss.get());
            } else {
                unsigned long r = oss.get();
                if(j == 3) // volume defaults to 64
                    EXPECT_EQ(0x40, r);
                else
                    EXPECT_EQ(0x00, r);
            }
        }
    }
}

TEST_F(ModWriterTest, write_TwoEmptySamplesThirdFull_WritesMaxSampleHeaders) {
    // arrange
    modio::Module module;

    modio::Sample sample{"SAMPLE03", 64, 0, 32};
    sample.setData(std::vector<unsigned char>(32, static_cast<unsigned char>(0xFF)));

    module.setSample(2, sample);

    // act
    std::stringstream oss;
    moduleWriter.write(module, oss);

    // assert
    oss.seekg(20, oss.beg);

    for(int i = 0; i < 31; ++i) {
        oss.seekg(22, oss.cur);

        char emptySample[8]{0x00, 0x10, 0x00, 0x40, 0x00, 0x00, 0x00, 0x20};
        for(int j = 0; j < sizeof(emptySample); ++j) {
            if (i == 2) {
                EXPECT_EQ(emptySample[j], oss.get());
            } else {
                unsigned long r = oss.get();
                if(j == 3) // volume defaults to 64
                    EXPECT_EQ(0x40, r);
                else
                    EXPECT_EQ(0x00, r);
            }
        }
    }
}

TEST_F(ModWriterTest, write_SampleNoName_NullPads) {
    // arrange
    modio::Module module;

    modio::Sample sample;
    sample.setData(std::vector<unsigned char>(32, 0xFF));

    module.setSample(0, sample);

    // act
    std::stringstream oss;
    moduleWriter.write(module, oss);

    // assert
    oss.seekg(2, oss.beg);
    int diff = 42 - 21; // TODO: Check if this really covers everything
    for(int i = 0; i < diff; ++i) {
        EXPECT_EQ(0x00, oss.get());
    }
}

TEST_F(ModWriterTest, write_SequenceOfOne_WritesOneSequenceAndPattern) {
    // arrange
    modio::Module module;
    module.setLength(1);

    // act
    std::stringstream oss;
    moduleWriter.write(module, oss);

    // assert
    oss.seekg(20, oss.beg); // skip name
    oss.seekg(module.samples().size() * 30, oss.cur); // skip sample headers
    EXPECT_EQ(1, oss.get()); // assert song positions
    oss.seekg(1, oss.cur); // skip tracker user data
    for(int i = 0; i < 128; ++i)
        EXPECT_EQ(0, oss.get());
    oss.seekg(4, oss.cur);

    char patternBuffer[1024];
    oss.read(patternBuffer, sizeof(patternBuffer));
    for(int i = 0; i < 1024; ++i)
        EXPECT_EQ(0, patternBuffer[i]);
}

TEST_F(ModWriterTest, write_SequenceRefToSixPatterns_WritesSixPatterns) {
    // arrange
    modio::Module module;
    module.set(0, 0);
    module.set(1, 1);
    module.set(2, 2);
    module.set(3, 3);
    module.set(4, 4);
    module.set(5, 5);
    module.setLength(6);

    // act
    std::stringstream oss;
    moduleWriter.write(module, oss);

    // assert
    oss.seekg(20, oss.beg); // skip name
    oss.seekg(module.samples().size() * 30, oss.cur); // skip sample headers
    EXPECT_EQ(6, oss.get()); // assert song positions
    oss.seekg(1, oss.cur); // skip tracker user data

    char patternTableBuffer[128];
    oss.read(patternTableBuffer, sizeof(patternTableBuffer));

    char expectedPatternTable[6]{0, 1, 2, 3, 4, 5};
    for(int i = 0; i < 128; ++i) {
        if(i < sizeof(expectedPatternTable))
            EXPECT_EQ(expectedPatternTable[i], patternTableBuffer[i]);
        else
            EXPECT_EQ(0x0, patternTableBuffer[i]);
    }
}

TEST_F(ModWriterTest, write_FullPattern_WritesFullPattern) {
    // arrange
    modio::Module module;

    modio::Pattern pattern;
    for(unsigned int channelIndex = 0; channelIndex < 4; ++channelIndex) {
        for(unsigned int divisionIndex = 0; divisionIndex < 64; ++divisionIndex) {
            pattern.set(channelIndex, divisionIndex, modio::Period(300), 1, modio::Effect(0x123));
        }
    }
    module.setPattern(0, pattern);

    // act
    std::stringstream oss;
    moduleWriter.write(module, oss);

    // assert
    oss.seekg(20, oss.beg); // skip name
    oss.seekg(module.samples().size() * 30, oss.cur); // skip sample headers
    oss.seekg(1, oss.cur); // skip song positions
    oss.seekg(1, oss.cur); // skip tracker user data
    oss.seekg(128, oss.cur); // skip pattern table
    oss.seekg(4, oss.cur); // skip signature

    char patternBuffer[1024];
    oss.read(patternBuffer, sizeof(patternBuffer));

    char expectedPattern[4]{0x01, 0x2C, 0x11, 0x23};
    for(int i = 0; i < sizeof(patternBuffer);) {
        for(int j = 0 ; j < sizeof(expectedPattern); ++j) {
            EXPECT_EQ(expectedPattern[j], patternBuffer[i++]);
        }
    }
}

TEST_F(ModWriterTest, write_EmptyPattern_WritesFullPatternWithPads) {
    // arrange
    modio::Module module;

    // act
    std::stringstream oss;
    moduleWriter.write(module, oss);

    // assert
    oss.seekg(20, oss.beg); // skip name
    oss.seekg(module.samples().size() * 30, oss.cur); // skip sample headers
    oss.seekg(134, oss.cur); // skip song positions, tracker user data, pattern table, signature

    char patternBuffer[1024];
    oss.read(patternBuffer, sizeof(patternBuffer));

    for(int i = 0; i < sizeof(patternBuffer);) {
        i += 1; // skip sample index (1)
        unsigned int period = patternBuffer[i++] << 16 | patternBuffer[i++] << 8 | patternBuffer[i++];
        EXPECT_EQ(0, period);
        i += 4; // skip sample index (2), effect
    }
}

TEST_F(ModWriterTest, write_SampleOnlyFirstIsValid_WriteOneSampleData) {
    // arrange
    modio::Module module;

    modio::Sample sample;
    std::vector<unsigned char> data(64, 0xFF);
    sample.setData(data);
    module.setSample(0, sample);

    // act
    std::stringstream oss;
    moduleWriter.write(module, oss);

    // assert
    oss.seekg(20, oss.beg); // skip name
    oss.seekg(module.samples().size() * 30, oss.cur); // skip sample headers
    oss.seekg(134, oss.cur); // skip song positions, tracker user data, pattern table, signature
    oss.seekg(1024, oss.cur); // skip song positions, tracker user data, pattern table, signature

    unsigned char sampleBuffer[65];
    oss.read(reinterpret_cast<char*>(&sampleBuffer), sizeof(sampleBuffer));

    for(int i = 0; i < 64; ++i)
        ASSERT_EQ(0xFF, sampleBuffer[i]);
    ASSERT_TRUE(oss.eof());
}

TEST_F(ModWriterTest, write_SampleOnlySecondIsValid_WriteTwoSampleData) {
    // arrange
    modio::Module module;

    modio::Sample sample;
    std::vector<unsigned char> data(64, 0xFF);
    sample.setData(data);
    module.setSample(1, sample);

    // act
    std::stringstream oss;
    moduleWriter.write(module, oss);

    // assert
    oss.seekg(20, oss.beg); // skip name
    oss.seekg(module.samples().size() * 30, oss.cur); // skip sample headers
    oss.seekg(134, oss.cur); // skip song positions, tracker user data, pattern table, signature
    oss.seekg(1024, oss.cur); // skip song positions, tracker user data, pattern table, signature

    unsigned char sampleBuffer[65];
    oss.read(reinterpret_cast<char*>(&sampleBuffer), sizeof(sampleBuffer));

    for(int i = 0; i < 64; ++i)
        ASSERT_EQ(0xFF, sampleBuffer[i]);
    ASSERT_TRUE(oss.eof());
}