cmake_minimum_required(VERSION 3.2.2 FATAL_ERROR)
project(libmodio_examples VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# executables
add_executable(create_module   create_module.cpp)
add_executable(generate_module generate_module.cpp)
add_executable(load_module     load_module.cpp)
add_executable(rewrite_module  rewrite_module.cpp)

target_include_directories(create_module   PUBLIC ../inc)
target_include_directories(generate_module PUBLIC ../inc)
target_include_directories(load_module     PUBLIC ../inc)
target_include_directories(rewrite_module  PUBLIC ../inc)

target_link_libraries(create_module libmodio)
target_link_libraries(load_module libmodio)

target_compile_features(create_module
    PUBLIC
        cxx_auto_type
        cxx_range_for
        cxx_generalized_initializers
)
target_compile_features(generate_module
    PUBLIC
        cxx_auto_type
        cxx_range_for
        cxx_generalized_initializers
)
target_compile_features(load_module
    PUBLIC
        cxx_auto_type
        cxx_range_for
        cxx_generalized_initializers
)
target_compile_features(rewrite_module
    PUBLIC
        cxx_auto_type
        cxx_range_for
        cxx_generalized_initializers
)
