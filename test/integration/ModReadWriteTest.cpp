#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "reader/ModReader.h"
#include "writer/ModWriter.h"

class ModReadWriteTest : public ::testing::TestWithParam<std::string> {
protected:
    modio::ModReader modReader;
    modio::ModWriter modWriter;
};

TEST_P(ModReadWriteTest, ReadWrite_IsIdentical) {
    // arrange
    std::string fileName{GetParam()};
    std::ifstream in{fileName};
    std::stringstream out;

    // act
    modio::Module module{modReader.read(in)};
    modWriter.write(module, out);

    // assert
    in.seekg(0, in.end);
    out.seekg(0, out.end);
    long long int inSize = in.tellg();
    long long int outSize = out.tellg();
    ASSERT_EQ(inSize, outSize);

    in.seekg(0, in.beg);
    out.seekg(0, out.beg);

    char inBuffer[inSize];
    char outBuffer[outSize];
    in.read(inBuffer, sizeof(inBuffer));
    out.read(outBuffer, sizeof(outBuffer));

    // TODO: Assert
}

INSTANTIATE_TEST_CASE_P(ModReadWriteTests, ModReadWriteTest, ::testing::Values("res/modules/musix-retrospective-milkytracker.mod"));