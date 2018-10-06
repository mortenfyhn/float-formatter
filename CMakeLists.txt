cmake_minimum_required(VERSION 3.5)

project(float-formatter LANGUAGES CXX)

set (CMAKE_CXX_STANDARD 11)

# Prepare "Catch" library for other executables
set(CATCH_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/catch)
add_library(Catch INTERFACE)
target_include_directories(Catch INTERFACE ${CATCH_INCLUDE_DIR})

# Collect all source files into a variable
set(
    TEST_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/test-main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/test-float-formatter.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/float-formatter.cpp
    )

add_executable(tests ${TEST_SOURCES})
target_link_libraries(tests Catch)

add_executable(main main.cpp float-formatter.cpp)
