#include <Channel.h>
#include "gtest/gtest.h"

class ChannelTest : public ::testing::Test {
protected:
    modio::Channel channel;
};

TEST_F(ChannelTest, getset_DivisionValid_SetsPeriod) {
    // arrange
    unsigned int divisionIndex{1};
    unsigned int periodData{200};
    unsigned int sampleIndex{4};

    modio::Period period(periodData);

    // act
    channel.set(divisionIndex, period, sampleIndex);

    // assert
    const modio::Division &division(channel.get(divisionIndex));
    EXPECT_EQ(periodData, division.period());
    EXPECT_EQ(sampleIndex, division.sampleIndex());
}

TEST_F(ChannelTest, getset_DivisionOnRange_ThrowsException) {
    // arrange
    unsigned int divisionIndex{63};
    unsigned int periodData{200};
    unsigned int sampleIndex{4};

    modio::Period period(periodData);

    // act / assert
    channel.set(divisionIndex, period, sampleIndex);

    // assert
    const modio::Division &division(channel.get(divisionIndex));
    EXPECT_EQ(periodData, division.period());
    EXPECT_EQ(sampleIndex, division.sampleIndex());
}

TEST_F(ChannelTest, getset_DivisionOutOfRange_ThrowsException) {
    // arrange
    unsigned int divisionIndex{64};
    unsigned int periodData{200};
    unsigned int sampleIndex{4};

    modio::Period period(periodData);

    // act / assert
    ASSERT_THROW({
        channel.set(divisionIndex, period, sampleIndex);
    }, std::out_of_range);
}

TEST_F(ChannelTest, get_DivisionOutOfRange_GetsDivision) {
    // arrange
    unsigned int divisionIndex{64};

    // act / assert
    ASSERT_THROW({
        channel.get(divisionIndex);
    }, std::out_of_range);
}
