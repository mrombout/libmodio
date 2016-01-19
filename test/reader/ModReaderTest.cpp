#include <fstream>
#include "gtest/gtest.h"
#include "reader/ModReader.h"
#include "Module.h"

class ModReaderTest : public ::testing::Test {
protected:
    ModReaderTest() {

    }

    modio::ModReader moduleReader;
    modio::Module module;
};

TEST_F(ModReaderTest, read_NameFull_ReadsCorrectModuleName) {
    // arrange
    std::ifstream in{"res/modules/fullname.mod", std::ios::in | std::ios::binary};

    // act
    module = moduleReader.read(in);
    auto result = module.name();

    // assert
    EXPECT_EQ("ABCDEFGHIJKLMNOPQRST", result);
}

TEST_F(ModReaderTest, read_NameHalf_ReadsCorrectModuleName) {
    // arrange
    std::ifstream in{"res/modules/halfname.mod", std::ios::in | std::ios::binary};

    // act
    module = moduleReader.read(in);
    auto result = module.name();

    // assert
    EXPECT_EQ("ABCDEFGHIJ", result);
}

TEST_F(ModReaderTest, read_SamplesSequential_ReadsAllSamples) {
    // arrange
    std::ifstream in{"res/modules/6_samples_sequential.mod", std::ios::in | std::ios::binary};

    // act
    module = moduleReader.read(in);

    // assert
    ASSERT_EQ(31, module.samples().size());

    auto samples = module.samples();
    for(int i = 0; i < 6; ++i) {
        auto sample = samples.at(i);

        auto title = sample.name();
        auto length = sample.length();
        auto volume = sample.volume();
        auto repeatStart = sample.repeatStart();
        auto repeatLength = sample.repeatLength();

        EXPECT_EQ("SAMPLE0" + std::to_string(i + 1), title);
        EXPECT_EQ(16, length);
        EXPECT_EQ(64, volume);
        EXPECT_EQ(0, repeatStart);
        EXPECT_EQ(16, repeatLength);
    }
}

TEST_F(ModReaderTest, read_SamplesNonsequential_ReadsAllSamples) {
    // arrange
    std::ifstream in{"res/modules/6_samples_nonsequential.mod", std::ios::in | std::ios::binary};

    // act
    module = moduleReader.read(in);

    // assert
    ASSERT_EQ(31, module.samples().size());

    auto samples = module.samples();
    for(int i = 0; i < 8; ++i) {
        if((i + 1) % 3 == 0)
            continue;
        auto sample = samples.at(i);

        auto title = sample.name();
        auto length = sample.length();
        auto volume = sample.volume();
        auto repeatOffset = sample.repeatStart();
        auto repeatLength = sample.repeatLength();

        EXPECT_EQ("SAMPLE0" + std::to_string(i + 1), title);
        EXPECT_EQ(16, length);
        EXPECT_EQ(64, volume);
        EXPECT_EQ(0, repeatOffset);
        EXPECT_EQ(16, repeatLength);
    }
}

TEST_F(ModReaderTest, read_PatternSizeOfOne_ReadsAllSamples) {
    // arrange
    std::ifstream in{"res/modules/simple_title_and_name.mod", std::ios::in | std::ios::binary};

    // act
    module = moduleReader.read(in);

    // assert
    ASSERT_EQ(1, module.length());
    EXPECT_EQ(0, module.get(0));
}

TEST_F(ModReaderTest, read_PatternSizeOfEleven_ReadsAllSamples) {
    // arrange
    std::ifstream in{"res/modules/sequence_123454321.mod", std::ios::in | std::ios::binary};

    // act
    module = moduleReader.read(in);

    // assert
    std::vector<unsigned int> sequence{0, 1, 2, 3, 4, 5, 4, 3, 2, 1, 0};
    ASSERT_EQ(sequence.size(), module.length());
    for(int i = 0; i < sequence.size(); ++i) {
        EXPECT_EQ(sequence[i], module.get(i));
    }
}

TEST_F(ModReaderTest, read_PatternSizeExceedsModuleLength_ThrowsException) {
    // arrange
    std::ifstream in{"res/modules/simple_title_and_name.mod", std::ios::in | std::ios::binary};

    // act
    module = moduleReader.read(in);

    // assert
    ASSERT_THROW({ module.get(1); }, std::invalid_argument);
}

TEST_F(ModReaderTest, read_ValidSignature_ReadsSignature) {
    // arrange
    std::ifstream in{"res/modules/sequence_123454321.mod", std::ios::in | std::ios::binary};

    // act
    module = moduleReader.read(in);

    // assert
    EXPECT_EQ("M.K.", module.signature());
}


TEST_F(ModReaderTest, read_InvalidStreamFileDoesNotExist_ThrowsException) {
    // arrange
    std::ifstream in{"this_file_does_not_exist.mod", std::ios::in | std::ios::binary};

    // act / assert
    EXPECT_THROW(module = moduleReader.read(in), std::istream::failure);
}
