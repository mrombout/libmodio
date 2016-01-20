#include "gtest/gtest.h"
#include "Sample.h"

class SampleTest : public ::testing::Test {
protected:
    modio::Sample sample;
};

TEST_F(SampleTest, resize_ResizeInWords_ResizesInBytes) {
    // arrange

    // act
    sample.resize(16);

    // assert
    EXPECT_EQ(16, sample.length());
}

TEST_F(SampleTest, length_ReturnsSizeInWords) {
    // arrange
    sample.resize(32);

    // act
    auto result = sample.length();

    // assert
    EXPECT_EQ(32, result);
}

TEST_F(SampleTest, setVolume_InvalidVolume_ThrowsException) {
    // arrange

    // act / assert
    ASSERT_THROW({
        sample.setVolume(128);
    }, std::invalid_argument);
}

TEST_F(SampleTest, setRepeatStart_RepeatStartPastLength_ThrowsException) {
    // arrange
    sample.resize(32);

    // act / assert
    ASSERT_THROW({
        sample.setRepeatStart(48);
    }, std::invalid_argument);
}

TEST_F(SampleTest, setRepeatLength_RepeatLengthPastLength_ThrowsException) {
    // arrange
    sample.resize(32);

    // act / assert
    ASSERT_THROW({
        sample.setRepeatLength(48);
    }, std::invalid_argument);
}