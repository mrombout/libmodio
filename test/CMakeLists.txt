# testing
set(TEST_FILES
    reader/ModReaderTest.cpp
    writer/ModWriterTest.cpp
    ChannelTest.cpp
    DivisionTest.cpp
    EffectTest.cpp
    ModuleTest.cpp
    NoteTest.cpp
    PatternTest.cpp
    SampleTest.cpp
    SequenceTest.cpp
)

add_executable(testmodio main.cpp ${TEST_FILES})
target_link_libraries(testmodio
    libmodio
    gtest
    gtest_main
    gmock)

enable_testing()
add_test(AllModioTests testmodio)