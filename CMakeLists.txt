cmake_minimum_required(VERSION 3.5)

project(float-formatter LANGUAGES CXX)

# Require C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Add CMake option for building tests
option(TESTS "Build test program" OFF)

# Create main executable
add_executable(main main.cpp)

# Create tests executable
if(TESTS)
    # Set up Catch library for linking with other executables
    add_library(catch INTERFACE)
    target_include_directories(catch INTERFACE ${CMAKE_PROJECT_DIR}/catch)

    # Create test executable
    add_executable(tests test-main.cpp test-float-formatter.cpp)
    target_link_libraries(tests catch)
endif(TESTS)
