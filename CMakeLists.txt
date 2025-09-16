cmake_minimum_required(VERSION 3.10)
project(SNNProject)

set(CMAKE_CXX_STANDARD 17)

include_directories(src)

add_executable(snn main.cpp src/LIFNeuron.cpp)
