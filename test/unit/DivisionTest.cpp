#include <Division.h>
#include "gtest/gtest.h"

class DivisionTest : public ::testing::Test {
protected:
    modio::Division division;
};

TEST_F(DivisionTest, set) {
    // arrange
    unsigned int periodData{123};
    modio::Period period(periodData);
    unsigned int sampleIndex{4};

    // act
    division.set(period, sampleIndex);

    // assert
    EXPECT_EQ(periodData, division.period().period());
    EXPECT_EQ(sampleIndex, division.sampleIndex());
}

TEST_F(DivisionTest, set2) {
    // arrange
    unsigned int periodData{123};
    modio::Period period(periodData);
    unsigned int sampleIndex{4};
    unsigned int effectData{567};
    modio::Effect effect(effectData);

    // act
    division.set(period, sampleIndex, effect);

    // assert
    EXPECT_EQ(periodData, division.period().period());
    EXPECT_EQ(sampleIndex, division.sampleIndex());
    EXPECT_EQ(effectData, division.effect());
}