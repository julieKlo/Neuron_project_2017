cmake_minimum_required (VERSION 2.6)

project (Neurons)

set(CMAKE_CXX_FLAGS "-W -Wall -pedantic -std=c++11")

enable_testing()
add_subdirectory(gtest)
include_directories(gtest/include gtest)

add_executable (Neurons main.cpp neuron.cpp Network.cpp Simulation.cpp)
add_executable (Neurons_unittest1 unitTest1.cpp neuron.cpp Network.cpp Simulation.cpp)

target_link_libraries(Neurons_unittest1 gtest gtest_main)
add_test(Neurons_unittest1 Neurons_unittest1)
