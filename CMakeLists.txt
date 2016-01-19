cmake_minimum_required(VERSION 3.3 FATAL_ERROR)
project(libmodio VERSION 0.0.1 LANGUAGES CXX C)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    src/main.cpp

    inc/reader/ModuleReader.h

    inc/reader/ModReader.h
    src/reader/ModReader.cpp

    inc/writer/ModuleWriter.h

    inc/writer/ModWriter.h
    src/writer/ModWriter.cpp

    inc/reader/ModReader.h
    src/reader/ModReader.cpp

    inc/Channel.h
    src/Channel.cpp

    inc/Division.h
    src/Division.cpp

    inc/Effect.h
    src/Effect.cpp

    inc/Module.h
    src/Module.cpp

    inc/Period.h
    src/Period.cpp

    inc/Pattern.h
    src/Pattern.cpp

    inc/Sample.h
    src/Sample.cpp

    inc/Sequence.h
    src/Sequence.cpp

    src/examples/create_module.cpp
    src/examples/generate_module.cpp
    src/examples/load_module.cpp
    src/examples/rewrite_module.cpp
)

# library
add_library(libmodio ${SOURCE_FILES})

target_include_directories(libmodio PUBLIC inc)
target_compile_features(libmodio
    PUBLIC
        cxx_auto_type
        cxx_range_for
        cxx_generalized_initializers
    )

# testing
add_subdirectory(lib/googletest/googlemock)
add_subdirectory(test)
