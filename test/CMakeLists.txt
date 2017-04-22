# testing
set(TEST_FILES
    integration/ModReadWriteTest.cpp
    unit/reader/ModReaderTest.cpp
    unit/writer/ModWriterTest.cpp
    unit/ChannelTest.cpp
    unit/DivisionTest.cpp
    unit/EffectTest.cpp
    unit/ModuleTest.cpp
    unit/PeriodTest.cpp
    unit/PatternTest.cpp
    unit/SampleTest.cpp
    unit/SequenceTest.cpp
)

add_executable(testmodio unit/main.cpp ${TEST_FILES})
target_link_libraries(testmodio
    libmodio
    gtest
    gtest_main
    gmock)

enable_testing()
add_test(AllModioTests testmodio)