cmake_minimum_required(VERSION 3.10)
project(SNNProject)

# Use C++17 standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include the src directory for header files
include_directories(src)

# Add executable and source files
add_executable(snn
    main.cpp
    src/LIFNeuron.cpp
    src/SNNNetwork.cpp  # optional, if you create this later
)
