#include "gtest/gtest.h"
#include <memory>
#include "Module.h"

class ModuleTest : public ::testing::Test {
protected:
    virtual void SetUp() {
        module.reset(new modio::Module());
    }

    std::unique_ptr<modio::Module> module;
};

TEST_F(ModuleTest, setName_6CharactersLong_SetsName) {
    // arrange

    // act
    module->setName("ABCDEF");

    // assert
    EXPECT_EQ(6, module->name().length());
}

TEST_F(ModuleTest, setName_19CharactersLong_SetsName) {
    // arrange

    // act
    module->setName("ABCDEFGHJIKLMNOPQRS");

    // assert
    EXPECT_EQ(19, module->name().length());
}

TEST_F(ModuleTest, setName_20CharactersLong_SetsName) {
    // arrange

    // act
    module->setName("ABCDEFGHJIKLMNOPQRST");

    // assert
    EXPECT_EQ(20, module->name().length());
}

TEST_F(ModuleTest, setName_21CharactersLong_ThrowsException) {
    // arrange

    // act / assert
    EXPECT_THROW(module->setName("ABCDEFGHJIKLMNOPQRSTU"), std::invalid_argument);
}

TEST_F(ModuleTest, setSignature_2CharactersLong_SetsName) {
    // arrange

    // act
    module->setSignature("AB");

    // assert
    EXPECT_EQ(2, module->signature().length());
}

TEST_F(ModuleTest, setSignature_3CharactersLong_SetsName) {
    // arrange

    // act
    module->setSignature("ABC");

    // assert
    EXPECT_EQ(3, module->signature().length());
}

TEST_F(ModuleTest, setSignature_4CharactersLong_SetsName) {
    // arrange

    // act
    module->setSignature("ABCD");

    // assert
    EXPECT_EQ(4, module->signature().length());
}

TEST_F(ModuleTest, setSignature_5CharactersLong_ThrowsException) {
    // arrange

    // act / assert
    EXPECT_THROW(module->setSignature("ABCDE"), std::invalid_argument);
}
